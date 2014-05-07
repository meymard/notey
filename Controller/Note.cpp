#include <stdio.h>
#include <iostream>
#include "../Header/Core.h"
#include "../Header/Console.h"

using namespace std;
using namespace Core::Controller;
using namespace Console::View;

std::vector<Core::Model::Note>* Note::notes = new std::vector<Core::Model::Note>();
DataSave* Note::db;

/**
 * Load Note
 *
 * @param int id The Note id
 *
 * @return Core::Model::Note
 */
Core::Model::Note Note::load(int id)
{
    Core::Model::Note note = Core::Model::Note("Ceci est un test", "Voiciint isSave =  son contenu");

    return note;
}

/**
 * Load all Note
 *
 * @return Core::Model::Note
 */
vector<Core::Model::Note>* Note::loadAll()
{
    Note::notes = Note::db->loadAll();

    return Note::notes;
}

/**
 * Add Note
 *
 * @return bool
 */
bool Note::add()
{
    Model::Note* note = new Model::Note();

    return Note::edit(note);
}

/**
 * Edit Note
 *
 * @return bool
 */
bool Note::edit()
{
    return Note::edit(Note::getNote());
}

/**
 * Edit Note
 *
 * @param Core::Model::Note* note The note to edit
 *
 * @return bool
 */
bool Note::edit(Core::Model::Note* note)
{
    note = Menu::editNote(note);

    return Note::save(note);
}

/**
 * Save Note
 *
 * @param Core::Model::Note* note The note to save
 *
 * @return bool
 */
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
    Menu::showNote(note);
}

/**
 * List notes
 *
 * @return int
 */
int Note::list()
{
    Menu::listNotes(Note::notes);
}

/**
 * Remove Note
 *
 * @return bool
 */
bool Note::remove()
{
    int id = Menu::removeNote();

    return Note::remove(id);
}

/**
 * Remove Note
 *
 * @param int id The Note id to remove
 *
 * @return bool
 */
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

/**
 * Get note
 *
 * @return Core::Model::Note*
 */
Core::Model::Note* Note::getNote()
{
    Core::Model::Note* note = new Core::Model::Note();

    int id = Menu::selectNote(Note::notes);

    for (vector<Core::Model::Note>::iterator it = Note::notes->begin(); it != Note::notes->end(); ++it) {
        if (id == it->getId()) {
            note = new Core::Model::Note(it);
            break;
        }
    }

    return note;
}

/**
 * show menu
 *
 * @return choice
 */
string Note::menu()
{
    string choice = Menu::show();

    return choice;
}

/**
 * End
 */
bool Note::end()
{
    Menu::end();
}
