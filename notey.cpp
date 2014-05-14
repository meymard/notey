#include <stdio.h>
#include <iostream>
#include "Header/Core.h"
#include "Header/Console.h"

using namespace std;
using namespace Core;

int main( int argc, const char* argv[] )
{
    // Prints each argument on the command line.
    for( int i = 0; i < argc; i++ )
    {
        printf( "arg %d: %s\n", i, argv[i] );
    }

    // initialize database
    const char* file = "/home/meymard/Dropbox/cpp/notes/bin/notey.db";
    Controller::Note::db = new Controller::DataSave(file);

    // Initialize View mode
    Console::View::Menu *view = new Console::View::Menu();
    Controller::Note::view = view;

    // initialize last Note id
    Model::Note::lastId = 0;

    Controller::Note::loadAll();

    string choice = "";
    do {
        choice = view->showMenu();

            if (choice == "list") {
                Controller::Note::list();
            } else if (choice == "add") {
                Controller::Note::add();
            } else if (choice == "edit") {
                Controller::Note::edit();
            } else if (choice == "show") {
                Controller::Note::show();
            } else if (choice == "remove") {
                Controller::Note::remove();
            }
    } while (choice != "quit");

    view->end();
}
