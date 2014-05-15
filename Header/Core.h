#ifndef CORE_H
#define CORE_H

#include <string>
#include <vector>
#include <stdio.h>

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

    namespace View
    {
        class NoteInterface
        {
            public:
                virtual void list(std::vector<Core::Model::Note>* notes) = 0;
                virtual Core::Model::Note* edit(Core::Model::Note* note) = 0;
                virtual void show(Core::Model::Note* note) = 0;
                virtual int select(std::vector<Core::Model::Note>* notes) = 0;
                virtual int remove() = 0;
        };
    }

    namespace Controller
    {
        /**
         * DataSave manage note
         */
        class DataSaveInterface
        {
            public:
                /**
                 * Save note
                 *
                 * @param Core::Model::Note* note
                 *
                 * @return bool
                 */
                virtual bool save(Core::Model::Note* note) = 0;

                /**
                 * Save all note
                 *
                 * @param std::vector<Core::Model::Note>* notes
                 *
                 * @return bool
                 */
                virtual bool saveAll(std::vector<Core::Model::Note>* notes) = 0;

                /**
                 * Load all note
                 *
                 * @return std::vector<Core::Model::Note>*
                 */
                virtual std::vector<Core::Model::Note>* loadAll() = 0;

                /**
                 * Load note
                 *
                 * @para int id
                 *
                 * @return Core::Model::Note
                 */
                virtual Core::Model::Note* load(int id) = 0;

                /**
                 * Remove note
                 *
                 * @param int id
                 *
                 * @return bool
                 */
                virtual bool remove(int id) = 0;
        };

        /**
         * Manage note
         */
        class Note
        {
            public:
                static Core::View::NoteInterface *view;
                /**
                 * @var std::vector<Core::Model::Note>*
                 */
                static std::vector<Core::Model::Note>* notes;

                /**
                 * @var Core::Controller::DataSaveInterface*
                 */
                static DataSaveInterface* db;

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
        };
    }
}

#endif

