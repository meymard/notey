#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include "../../Header/Core.h"
#include "../../Header/Gtk.h"

using namespace Gtk::View;
using namespace Core;

/**
 *
 */
NoteyWindow::NoteyWindow()
: selectNote(Gtk::ORIENTATION_HORIZONTAL),
  noteInfo(Gtk::ORIENTATION_VERTICAL)
{
    set_title("Notey");

    set_border_width(5);
    set_default_size(400, 200);

    add(selectNote);

    // Now add tree and note info
    selectNote.add1(mTreeView);
    selectNote.add2(noteInfo);

    // Add note info
    noteInfo.add1(titleTextView);
    noteInfo.add2(bodyTextView);

    //Only show the scrollbars when they are necessary:
    m_scrolledwindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    //Create the Tree model:
    mRefTreeModel = Gtk::ListStore::create(mColumns);
    mTreeView.set_model(mRefTreeModel);

    //Fill the TreeView's model
    for (std::vector<Model::Note>::iterator it = Controller::Note::notes->begin(); it != Controller::Note::notes->end(); ++it) {
        Gtk::TreeModel::Row row = *(mRefTreeModel->append());
        row[mColumns.mColId] = it->getId();
        row[mColumns.mColName] = it->getTitle();
    }

    //Add the TreeView's view columns:
    //This number will be shown with the default numeric formatting.
    mTreeView.append_column("ID", mColumns.mColId);
    mTreeView.append_column("Name", mColumns.mColName);

    //Make all the columns reorderable:
    //This is not necessary, but it's nice to show the feature.
    //You can use TreeView::set_column_drag_function() to more
    //finely control column drag and drop.
    for(guint i = 0; i < 2; i++)
    {
        Gtk::TreeView::Column* pColumn = mTreeView.get_column(i);
        pColumn->set_reorderable();
    }

    // Handler Click treeview
    Glib::RefPtr<Gtk::TreeView::Selection> refSelection = mTreeView.get_selection();
    refSelection->signal_changed().connect(sigc::mem_fun(*this, &NoteyWindow::onNoteClick), false);

    show_all_children();
}

void NoteyWindow::onNoteClick()
{
    Model::Note* note = this->getCurrentNote();
    // Fill title
    const Glib::RefPtr<Gtk::TextBuffer>& titleTextBuffer = Gtk::TextBuffer::create();
    titleTextBuffer->set_text(note->getTitle());
    titleTextView.set_buffer(titleTextBuffer);
    // Event on title
    titleTextBuffer->signal_changed().connect(sigc::mem_fun(*this, &NoteyWindow::onTextUpdate), false);

    // Fill body
    const Glib::RefPtr<Gtk::TextBuffer>& bodyTextBuffer = Gtk::TextBuffer::create();
    bodyTextBuffer->set_text(note->getBody());
    bodyTextView.set_buffer(bodyTextBuffer);
    // Event on body
    bodyTextBuffer->signal_changed().connect(sigc::mem_fun(*this, &NoteyWindow::onTextUpdate), false);
}

void NoteyWindow::onTextUpdate()
{
    Model::Note* note = this->getCurrentNote();
    note->setTitle(titleTextView.get_buffer()->get_text());
    note->setBody(bodyTextView.get_buffer()->get_text());

    Controller::Note::save(note);
}

Model::Note* NoteyWindow::getCurrentNote()
{
    Glib::RefPtr<Gtk::TreeView::Selection> refSelection = mTreeView.get_selection();

    Gtk::TreeModel::iterator iter = refSelection->get_selected();
    if(iter)
    {
        int id = (*iter)[mColumns.mColId];

        // Get Note
        return Controller::Note::getNote(id);
    } else {
        // TODO Throw exception
        return NULL;
    }
}

/** Notey Application */

NoteyApplication::NoteyApplication()
    : Gtk::Application("org.gtkmm.notey.application", Gio::APPLICATION_HANDLES_OPEN)
{
    Glib::set_application_name("Notey Application");
}

Glib::RefPtr<NoteyApplication> NoteyApplication::create()
{
    return Glib::RefPtr<NoteyApplication>( new NoteyApplication() );
}

void NoteyApplication::create_window(const Glib::RefPtr<Gio::File>& file)
{
    NoteyWindow* window = new NoteyWindow();

    //Make sure that the application runs for as long this window is still open:
    add_window(*window);

    //Delete the window when it is hidden.
    //That's enough for this simple example.
    window->signal_hide().connect(sigc::bind<Gtk::Window*>(sigc::mem_fun(*this,
                    &NoteyApplication::on_window_hide), window));

    window->show();

    if(!file)
    {
        //This is probably a new empty file, as a result of an activation rather
        //than an open.
        return;
    }

}

void NoteyApplication::on_window_hide(Gtk::Window* window)
{
    delete window;
}

void NoteyApplication::on_activate()
{
    //std::cout << "debug1: " << G_STRFUNC << std::endl;
    // The application has been started, so let's show a window.
    // A real application might want to reuse this "empty" window in on_open(),
    // when asked to open a file, if no changes have been made yet.
    create_window();
}

void NoteyApplication::on_open(const Gio::Application::type_vec_files& files,
        const Glib::ustring& hint)
{
    // The application has been asked to open some files,
    // so let's open a new window for each one.
    //std::cout << "debug: files.size()=" << files.size() << std::endl;
    for(guint i = 0; i < files.size(); i++)
    {
        Glib::RefPtr<Gio::File> file = files[i];
        if(!file)
        {
            std::cerr << G_STRFUNC << ": file is null." << std::endl;
        }
        else
            create_window(file);
    }

    //Call the base class's implementation:
    Gtk::Application::on_open(files, hint);
}
