#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "../../Header/Console.h"
#include "../../Header/Core.h"

using namespace std;
using namespace Console::View;
using namespace Core::Model;

const string COLOR_DEFAULT     = "\33[0m";

const string COLOR_RED         = "\33[0;31m";
const string COLOR_GREEN       = "\33[0;32m";
const string COLOR_ORANGE      = "\33[0;33m";
const string COLOR_BLUE        = "\33[0;34m";
const string COLOR_PURPLE      = "\33[0;35m";
const string COLOR_CYAN        = "\33[0;36m";
const string COLOR_GREY        = "\33[0;37m";

const string COLOR_BG_BLACK    = "\33[0;40m";
const string COLOR_BG_RED      = "\33[0;41m";
const string COLOR_BG_GREEN    = "\33[0;42m";
const string COLOR_BG_ORANGE   = "\33[0;43m";
const string COLOR_BG_BLUE     = "\33[0;44m";
const string COLOR_BG_PURPLE   = "\33[0;45m";
const string COLOR_BG_CYAN     = "\33[0;46m";
const string COLOR_BG_GREY     = "\33[0;47m";

void Menu::list(std::vector<Core::Model::Note>* notes) {
    cout << COLOR_GREEN;
    cout << "##################" << endl;
    cout << "###### List ######" << endl;
    cout << "##################" << endl;
    cout << COLOR_DEFAULT;

    for (std::vector<Core::Model::Note>::iterator it = notes->begin(); it != notes->end(); ++it) {
        cout << "#" << it->getId() << ": ";
        cout << COLOR_CYAN << it->getTitle() << COLOR_DEFAULT <<  endl;
        //cout << it->getBody() << endl;
        cout << endl;
    }
    cout << endl;
}

Core::Model::Note* Menu::edit(Core::Model::Note* note)
{
    bool edit;
    cout << COLOR_GREEN;
    cout << "##################" << endl;
    if (note->getId() == 0) {
        edit = false;
        cout << "###### add  ######" << endl;
    } else {
        edit = true;
        cout << "###### edit ######" << endl;
    }
    cout << "##################" << endl;
    cout << COLOR_DEFAULT;

    // Set Title
    char title[256];
    cout << "Set title:";
    if (edit) {
        cout << " (empty if not change)" << endl;
    }
    cin.ignore();
    cin.getline(title, 256);
    if (!edit || string(title) != "") {
        note->setTitle(string(title));
    }

    // Set Body
    string body, bodyLine;
    cout << "Set body:" << endl;
    if (edit) {
        cout << COLOR_ORANGE << " (empty if not change)" << COLOR_DEFAULT;
    }
    cout << endl;
    cout << COLOR_ORANGE << "(end by blank line)" << COLOR_DEFAULT << endl;

    do {
        getline(cin, bodyLine);
        if (bodyLine != "") {
            body += '\n' + bodyLine;
        }
    } while (bodyLine != "");

    if (!edit || body != "") {
        note->setBody(body);
    }

    cout << endl;

    return note;
}

void Menu::show(Note* note)
{
    cout << "#" << note->getId() << endl;
    cout << COLOR_CYAN << note->getTitle() << COLOR_DEFAULT <<  endl;
    cout << note->getBody() << endl;
    cout << endl;

    // Wait user action for continue
    char title[50];
    cout << COLOR_ORANGE << "Press enter to continue";
    cin.ignore();
    cin.getline(title, 50);
    cout << COLOR_DEFAULT << endl;
}

int Menu::select(vector<Note>* notes)
{
    Menu::list(notes);

    cout << COLOR_GREEN;
    cout << "Enter a note id :";
    cout << COLOR_DEFAULT;

    int id;
    cin >> id;

    return id;
}

int Menu::remove()
{
    cout << COLOR_RED;
    cout << "##################" << endl;
    cout << "##### Remove #####" << endl;
    cout << "##################" << endl;
    cout << COLOR_DEFAULT;

    int id;
    cout << "Enter the id:";
    cin >> id;

    return id;
}

string Menu::showMenu() {
    cout << COLOR_ORANGE;
    cout << "####################" << endl;
    cout << "# " << COLOR_DEFAULT << "l" << COLOR_ORANGE << ": List note     #" << endl;
    cout << "# " << COLOR_DEFAULT << "s" << COLOR_ORANGE << ": Show note     #" << endl;
    cout << "# " << COLOR_DEFAULT << "a" << COLOR_ORANGE << ": Add note      #" << endl;
    cout << "# " << COLOR_DEFAULT << "e" << COLOR_ORANGE << ": Edit note     #" << endl;
    cout << "# " << COLOR_DEFAULT << "r" << COLOR_ORANGE << ": Remove note   #" << endl;
    cout << "# " << COLOR_DEFAULT << "q" << COLOR_ORANGE << ": quit          #" << endl;
    cout << "####################" << endl;
    cout << COLOR_DEFAULT;
    cout << endl;

    char choice;
    cout << "Choice:";
    cin >> choice;

    switch (choice) {
        case 'a':
            return "add";
            break;

        case 'e':
            return "edit";
            break;

        case 'r':
            return "remove";
            break;

        case 'l':
            return "list";
            break;

        case 's':
            return "show";
            break;

        case 'q':
            return "quit";
            break;

        default:
            return "";
    }
}

bool Menu::end() {
    cout << COLOR_BG_GREEN;
    cout << "Good bye";
    cout << COLOR_DEFAULT;
    cout << endl;

    return true;
}
