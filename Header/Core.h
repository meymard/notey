#ifndef CORE_H
#define CORE_H

#include <string>
#include <vector>
#include <stdio.h>
#include <sqlite3.h>

namespace Core
{
    namespace Model
    {
        /**
         * Note model
         */
        class Note
        {
            public:
                /**
                 * @var int
                 */
                static int lastId;

                /**
                 * Constructor
                 */
                Note();

                /**
                 * Constructor
                 *
                 * @param std::string title Title
                 * @param std::string body  Body
                 */
                Note(std::string title, std::string body);

                /**
                 * Constructor
                 *
                 * @param int         id    Id
                 * @param std::string title Title
                 * @param std::string body  Body
                 */
                Note(int id, std::string title, std::string body);

                /**
                 * Constructor
                 *
                 * @param std::vector<Core::Model::Note>::iterator it
                 */
                Note(std::vector<Core::Model::Note>::iterator it);

                /**
                 * Get id
                 *
                 * @return int
                 */
                int getId();

                /**
                 * Set id
                 *
                 * @param int id
                 *
                 * @return Note&
                 */
                Note& setId(int id);

                /**
                 * Get title
                 *
                 * @return std::string
                 */
                std::string getTitle();

                /**
                 * Set title
                 *
                 * @param std::string title
                 *
                 * @return Note&
                 */
                Note& setTitle(std::string title);

                /**
                 * Get body
                 *
                 * @return std::string
                 */
                std::string getBody();

                /**
                 * Set body
                 *
                 * @param std::string body
                 *
                 * @return Note&
                 */
                Note& setBody(std::string body);

            protected:
                /**
                 * @var std::string
                 */
                std::string title;

                /**
                 * @var std::string
                 */
                std::string body;

            private:
                /**
                 * @var int
                 */
                int id;
        };
    }

    namespace Controller
    {
        /**
         * DataSave manage note in sqlite
         */
        class DataSave
        {
            private:
                /**
                 * @var sqlite3
                 */
                sqlite3 *db;

            protected:
                /**
                 * Sqlite3 callback
                 *
                 * @var void*  NotUsed   Note used var
                 * @var int    argc      Arg count
                 * @var char** argv      Arg values
                 * @var char** azColName Col name
                 *
                 * @return int
                 */
                static int callback(void *NotUsed, int argc, char** argv, char **azColName);

                /**
                 * Escape string for sql query
                 *
                 * @param std::string text String to escape
                 *
                 * @return std::string
                 */
                std::string sqlEscape(std::string text);

            public:
                /**
                 * Constructor
                 *
                 * @var const char* file Sqlite file
                 */
                DataSave(const char* file);

                /**
                 * Destructor
                 */
                ~DataSave();

                /**
                 * Save note in database
                 *
                 * @param Core::Model::Note* note
                 *
                 * @return bool
                 */
                bool save(Core::Model::Note* note);

                /**
                 * Save all note in database
                 *
                 * @param std::vector<Core::Model::Note>* notes
                 *
                 * @return bool
                 */
                bool saveAll(std::vector<Core::Model::Note>* notes);

                /**
                 * Load all note from database
                 *
                 * @return std::vector<Core::Model::Note>*
                 */
                std::vector<Core::Model::Note>* loadAll();

                /**
                 * Load note from database
                 *
                 * @para int id
                 *
                 * @return Core::Model::Note
                 */
                Core::Model::Note load(int id);

                /**
                 * Remove note in database
                 *
                 * @param int id
                 *
                 * @return bool
                 */
                bool remove(int id);
        };

        /**
         * Manage note
         */
        class Note
        {
            public:
                /**
                 * @var std::vector<Core::Model::Note>*
                 */
                static std::vector<Core::Model::Note>* notes;

                /**
                 * @var Core::Controller::DataSave*
                 */
                static Core::Controller::DataSave* db;

                /**
                 * Load note
                 *
                 * @param int id
                 *
                 * @return Core::Model::Note
                 */
                static Core::Model::Note load(int id);

                /**
                 * Load all note
                 *
                 * @return std::vector<Core::Model::Note>*
                 */
                static std::vector<Core::Model::Note>* loadAll();

                /**
                 * Get note
                 *
                 * @return Core::Model::Note*
                 */
                static Core::Model::Note* getNote();

                /**
                 * Add note
                 *
                 * @return bool
                 */
                static bool add();

                /**
                 * Edit note
                 *
                 * @return bool
                 */
                static bool edit();

                /**
                 * Edit note
                 *
                 * @param Core::Model::Note* note
                 *
                 * @return bool
                 */
                static bool edit(Core::Model::Note* note);

                /**
                 * Save note
                 *
                 * @param Core::Model::Note* note
                 *
                 * @return bool
                 */
                static bool save(Core::Model::Note* note);

                /**
                 * Show note
                 */
                static void show();

                /**
                 * Remove note
                 *
                 * @return bool
                 */
                static bool remove();

                /**
                 * Remove note
                 *
                 * @param int id
                 *
                 * @return bool
                 */
                static bool remove(int id);

                /**
                 * List note
                 *
                 * @return int
                 */
                static int list();

                /**
                 * Show menu
                 *
                 * @return std::string
                 */
                static std::string menu();

                /**
                 * Show end message
                 */
                static bool end();
        };
    }

    namespace View
    {
        class Menu
        {
            public:
                //virtual void listNotes(Core::Model::Note notes[]) = 0;
        };
    }
}

#endif

