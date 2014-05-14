#include <stdio.h>
#include <iostream>
#include "../Header/Core.h"
#include "../Header/Console.h"

using namespace std;
using namespace Core::Controller;
using namespace Console::View;

Core::View::NoteInterface *Note::view;
std::vector<Core::Model::Note>* Note::notes = new std::vector<Core::Model::Note>();
DataSave* Note::db;

Core::Model::Note Note::load(int id)
{
    Core::Model::Note note = Core::Model::Note("Ceci est un test", "Voici son contenu");

    return note;
}

vector<Core::Model::Note>* Note::loadAll()
{
    Note::notes = Note::db->loadAll();

    return Note::notes;
}

bool Note::add()
{
    Model::Note* note = new Model::Note();

    return Note::edit(note);
}

bool Note::edit()
{
    return Note::edit(Note::getNote());
}

bool Note::edit(Core::Model::Note* note)
{
    note = Note::view->edit(note);

    return Note::save(note);
}

bool Note::save(Core::Model::Note* note)
{
    Note::db->save(note);

    for (std::vector<Core::Model::Note>::iterator it = Note::notes->begin(); it != notes->end(); ++it) {
        if (it->getId() == note->getId()) {
            Note::notes->erase(it);
            break;
        }
    }
    Note::notes->push_back(*note);

    return true;
}

void Note::show()
{
    Core::Model::Note* note = Note::getNote();
    Note::view->show(note);
}

int Note::list()
{
    Note::view->list(Note::notes);
}

bool Note::remove()
{
    int id = Note::view->remove();

    return Note::remove(id);
}

bool Note::remove(int id)
{
    // Remove on database
    Note::db->remove(id);
    // Remove on vector
    for (std::vector<Core::Model::Note>::iterator it = notes->begin(); it != notes->end(); ++it) {
        if (it->getId() == id) {
            notes->erase(it);

            return true;
        }
    }

    return false;
}

Core::Model::Note* Note::getNote()
{
    Core::Model::Note* note = new Core::Model::Note();

    int id = Note::view->select(Note::notes);

    for (vector<Core::Model::Note>::iterator it = Note::notes->begin(); it != Note::notes->end(); ++it) {
        if (id == it->getId()) {
            note = new Core::Model::Note(it);
            break;
        }
    }

    return note;
}

/*string Note::menu()
{
    string choice = Note::view->showMenu();

    return choice;
}*/

/*bool Note::end()
{
    Note::view->end();
}*/
