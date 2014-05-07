#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include <vector>

#include "Core.h"

namespace Console
{
    namespace View
    {
        class Menu: public Core::View::Menu
        {
            public:
                static void listNotes(std::vector<Core::Model::Note>* notes);
                static std::string show();
                static Core::Model::Note* editNote(Core::Model::Note* note);
                static void showNote(Core::Model::Note* note);
                static int selectNote(std::vector<Core::Model::Note>* notes);
                static int removeNote();
                static bool end();
        };
    }
}

#endif
