#ifndef GTK_H
#define GTK_H

#include <gtkmm.h>
#include <gtkmm/button.h>
#include "Core.h"

namespace Gtk
{
    namespace View
    {
        class NoteyApplication: public Gtk::Application
        {
            protected:
                NoteyApplication();

            public:
                static Glib::RefPtr<NoteyApplication> create();

            protected:
                //Overrides of default signal handlers:
                virtual void on_activate();
                virtual void on_open(const Gio::Application::type_vec_files& files, const Glib::ustring& hint);

            private:
                void create_window(const Glib::RefPtr<Gio::File>& file = Glib::RefPtr<Gio::File>());

                void on_window_hide(Gtk::Window* window);
        };

        class NoteyWindow: public Gtk::ApplicationWindow
        {
            public:

                //We do not take the file as a constructor parameter,
                //so we can separate window creation and hiding of the window
                //when loading fails.
                explicit NoteyWindow();

                bool load_file(const Glib::RefPtr<Gio::File>& file);

            protected:
                void fill_buffers();

                Gtk::Paned selectNote;
                Gtk::Paned noteInfo;
                Gtk::ScrolledWindow m_scrolledwindow;

                Core::Model::Note* getCurrentNote();

                //Signal handlers:
                void onNoteClick();
                void onTextUpdate();

                //Tree model columns:
                class ModelColumns : public Gtk::TreeModel::ColumnRecord
                {
                    public:

                        ModelColumns()
                        { add(mColId); add(mColName);}

                        Gtk::TreeModelColumn<unsigned int> mColId;
                        Gtk::TreeModelColumn<Glib::ustring> mColName;
                };

                ModelColumns mColumns;

                //Child widgets:
                Gtk::Box mVBox;

                Gtk::ScrolledWindow mScrolledWindow;
                Gtk::TreeView mTreeView;
                Glib::RefPtr<Gtk::ListStore> mRefTreeModel;

                Gtk::TextView titleTextView;
                Gtk::TextView bodyTextView;
        };
    }
}

#endif
