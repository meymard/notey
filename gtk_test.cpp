#include <iostream>
#include "Header/Core.h"
#include "Header/Gtk.h"
#include "Header/Sqlite.h"
#include <gtkmm.h>
#include <gtkmm/window.h>

using namespace std;
using namespace Gtk::View;
using namespace Core;

int main( int argc, char* argv[] )
{
    // initialize database
    const char* file = "/home/meymard/Dropbox/cpp/notes/bin/notey.db";
    Sqlite::Controller::DataSave *db = new Sqlite::Controller::DataSave(file);
    Controller::Note::db = db;

    Controller::Note::loadAll();

    Glib::RefPtr<NoteyApplication> application = NoteyApplication::create();

    const int status = application->run(argc, argv);
    return status;
}
