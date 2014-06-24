#include <stdio.h>
#include <iostream>
#include <vector>
#include "../../Header/Core.h"
#include "../../Header/Gtk.h"

using namespace Gtk::View;
using namespace Core;

NoteyWindow::NoteyWindow()
: mVBox(Gtk::ORIENTATION_VERTICAL),
  mButtonQuit("Quit"),
  m_Button_Buffer1("B 1"),
  m_Button_Buffer2("B 2")

{
    set_title("Notey");

    set_border_width(5);
    set_default_size(400, 200);

    add(mVBox);

    m_scrolledwindow.add(mTreeView);
    m_scrolledwindow.add(m_TextView);

    //Only show the scrollbars when they are necessary:
    m_scrolledwindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    mVBox.pack_start(m_scrolledwindow);
    mVBox.pack_start(mButtonBox, Gtk::PACK_SHRINK);

    mButtonBox.pack_start(m_Button_Buffer1, Gtk::PACK_SHRINK);
    mButtonBox.pack_start(m_Button_Buffer2, Gtk::PACK_SHRINK);
    mButtonBox.pack_start(mButtonQuit, Gtk::PACK_SHRINK);
    mButtonBox.set_border_width(5);
    mButtonBox.set_layout(Gtk::BUTTONBOX_END);
    mButtonQuit.signal_clicked().connect( sigc::mem_fun(*this,
                &NoteyWindow::onButtonQuit) );

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

    mVBox.pack_start(mTreeView);

    show_all_children();
}

void NoteyWindow::fill_buffers()
{
  m_refTextBuffer1 = Gtk::TextBuffer::create();
  m_refTextBuffer1->set_text("This is the text from TextBuffer #1.");

  m_refTextBuffer2 = Gtk::TextBuffer::create();
  m_refTextBuffer2->set_text(
          "This is some alternative text, from TextBuffer #2.");

}

void NoteyWindow::on_button_buffer1()
{
  m_TextView.set_buffer(m_refTextBuffer1);
}

void NoteyWindow::on_button_buffer2()
{
  m_TextView.set_buffer(m_refTextBuffer2);
}

void NoteyWindow::onButtonQuit()
{
    hide();
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
