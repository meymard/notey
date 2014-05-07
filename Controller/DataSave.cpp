#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <sqlite3.h>
#include <sstream>
#include "../Header/Core.h"

using namespace std;
using namespace Core::Controller;

DataSave::DataSave(const char* file)
{
    int rc = sqlite3_open(file, &this->db);

    if (true || rc) {
        char* zErrMsg;
        const char* query = "CREATE TABLE note (id INTEGER PRIMARY KEY AUTOINCREMENT, title VARCHAR(255), body TEXT)";

        int rc = sqlite3_exec(this->db, query, DataSave::callback, 0, &zErrMsg);
        if(rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
        }
    } else {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(this->db));
        sqlite3_close(this->db);
        // Throw error
    }
}

DataSave::~DataSave()
{
    sqlite3_close(this->db);
}

int DataSave::callback(void *NotUsed, int argc, char** argv, char **azColName)
{
    for (int i=0; i < argc; i++) {
        printf("%s = %s\n", azColName[1], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

bool DataSave::save(Core::Model::Note* note)
{
    char* zErrMsg = 0;
    string query;
    bool edit;

    if (note->getId() > 0) {
        edit = true;
        ostringstream ossId;
        ossId << note->getId();

        query = "UPDATE note set title='"+this->sqlEscape(note->getTitle())+"', body='"+this->sqlEscape(note->getBody())+"' WHERE id="+ossId.str();
    } else {
        edit = false;
        query = "INSERT INTO note (title, body) VALUES ('"+this->sqlEscape(note->getTitle())+"', '"+this->sqlEscape(note->getBody())+"')";
    }

    int rc = sqlite3_exec(this->db, query.c_str(), DataSave::callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);

        return false;
    }
    if (!edit) {
        int newId = (int)sqlite3_last_insert_rowid(this->db);
        note->setId(newId);
    }

    return true;
}

bool DataSave::saveAll(vector<Core::Model::Note>* notes)
{
    return false;
}

vector<Core::Model::Note>* DataSave::loadAll()
{
    vector<Core::Model::Note>* notes = new vector<Core::Model::Note>();

    char* zErrMsg = 0;

    sqlite3_stmt *statement;

    const char *query = "SELECT id, title, body FROM note";

    if (sqlite3_prepare(this->db, query, -1, &statement, 0) == SQLITE_OK)
    {
        int ctotal = sqlite3_column_count(statement);
        int res = 0;

        while (true)
        {
            res = sqlite3_step(statement);

            if ( res == SQLITE_ROW )
            {
                int id = sqlite3_column_int(statement, 0);
                string title = (char*)sqlite3_column_text(statement, 1);
                string body = (char*)sqlite3_column_text(statement, 2);
                Core::Model::Note* note = new Core::Model::Note(id, title, body);
                notes->push_back(*note);

                cout << "Load note: " << note->getTitle() << endl;
            }

            if ( res == SQLITE_DONE || res==SQLITE_ERROR)
            {
                cout << "done " << endl;
                break;
            }
        }
    }

    return notes;
}

bool DataSave::remove(int id)
{
    char* zErrMsg = 0;
    ostringstream ossId;
    ossId << id;
    //int id = note->getId();
    string query = "DELETE FROM note WHERE id='"+ossId.str()+"';";

    int rc = sqlite3_exec(this->db, query.c_str(), DataSave::callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);

        return false;
    }

    return true;
}

string DataSave::sqlEscape(string text)
{
    size_t index = 0;
    while (true) {
        /* Locate the substring to replace. */
        index = text.find("'", index);
        if (index == string::npos) break;

        /* Make the replacement. */
        text.replace(index, 1, "''");

        /* Advance index forward so the next iteration doesn't pick it up as well. */
        index += 3;
    }

    return text;
}
