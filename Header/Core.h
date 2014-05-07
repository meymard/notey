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
        class Note
        {
            public:
                static int lastId;

                Note();
                Note(std::string title, std::string body);
                Note(int id, std::string title, std::string body);
                Note(std::vector<Core::Model::Note>::iterator it);

                int getId();
                Note& setId(int id);
                std::string getTitle();
                Note& setTitle(std::string title);
                std::string getBody();
                Note& setBody(std::string body);

            protected:
                std::string title;
                std::string body;

            private:
                int id;
        };
    }

    namespace Controller
    {
        class DataSave
        {
            private:
                sqlite3 *db;

            protected:
                static int callback(void *NotUsed, int argc, char** argv, char **azColName);
                std::string sqlEscape(std::string text);

            public:
                DataSave(const char* file);
                ~DataSave();

                bool save(Core::Model::Note* note);
                bool saveAll(std::vector<Core::Model::Note>* notes);
                std::vector<Core::Model::Note>* loadAll();
                Core::Model::Note load(int id);
                bool remove(int id);
        };

        class Note
        {
            public:
                static std::vector<Core::Model::Note>* notes;
                static Core::Controller::DataSave* db;

                static Core::Model::Note load(int id);
                static std::vector<Core::Model::Note>* loadAll();
                static Core::Model::Note* getNote();
                static bool add();
                static bool edit();
                static bool edit(Core::Model::Note* note);
                static bool save(Core::Model::Note* note);
                static void show();
                static bool remove();
                static bool remove(int id);
                static int list();
                static std::string menu();
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

