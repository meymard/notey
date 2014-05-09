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
                /**
                 * Show notes list
                 *
                 * @param std::vector<Core::Model::Note>* notes All notes
                 *
                 * @return void
                 */
                static void listNotes(std::vector<Core::Model::Note>* notes);

                /**
                 * Show menu
                 *
                 * @return std::string User choice
                 */
                static std::string show();

                /**
                 * Edit note
                 *
                 * @param Core::Model::Note* note
                 *
                 * @param Core::Model::Note*
                 */
                static Core::Model::Note* editNote(Core::Model::Note* note);

                /**
                 * Show note
                 *
                 * @param Core::Model::Note* note
                 *
                 * @return void
                 */
                static void showNote(Core::Model::Note* note);

                /**
                 * Select note
                 *
                 * @param std::vector<Core::Model::Note>* notes All notes
                 *
                 * @return int The selected note
                 */
                static int selectNote(std::vector<Core::Model::Note>* notes);

                /**
                 * Remove note
                 *
                 * @return int Note to remove
                 */
                static int removeNote();

                /**
                 * Show end message
                 *
                 * @return bool
                 */
                static bool end();
        };
    }
}

#endif
