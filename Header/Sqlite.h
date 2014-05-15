#ifndef SQLITE_H
#define SQLITE_H

#include <string>
#include <vector>
#include <stdio.h>
#include <sqlite3.h>

#include "Core.h"

namespace Sqlite
{
    namespace Controller
    {
        /**
         * DataSave manage note in sqlite
         */
        class DataSave: public Core::Controller::DataSaveInterface
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
                Core::Model::Note* load(int id);

                /**
                 * Remove note in database
                 *
                 * @param int id
                 *
                 * @return bool
                 */
                bool remove(int id);
        };
    }
}

#endif

