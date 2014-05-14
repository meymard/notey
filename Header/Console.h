#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include <vector>

#include "Core.h"

namespace Console
{
    namespace View
    {
        class Menu: public Core::View::NoteInterface
        {
            public:
                /**
                 * Show notes list
                 *
                 * @param std::vector<Core::Model::Note>* notes All notes
                 *
                 * @return void
                 */
                void list(std::vector<Core::Model::Note>* notes);

                /**
                 * Show menu
                 *
                 * @return std::string User choice
                 */
                std::string showMenu();

                /**
                 * Edit note
                 *
                 * @param Core::Model::Note* note
                 *
                 * @param Core::Model::Note*
                 */
                Core::Model::Note* edit(Core::Model::Note* note);

                /**
                 * Show note
                 *
                 * @param Core::Model::Note* note
                 *
                 * @return void
                 */
                void show(Core::Model::Note* note);

                /**
                 * Select note
                 *
                 * @param std::vector<Core::Model::Note>* notes All notes
                 *
                 * @return int The selected note
                 */
                int select(std::vector<Core::Model::Note>* notes);

                /**
                 * Remove note
                 *
                 * @return int Note to remove
                 */
                int remove();

                /**
                 * Show end message
                 *
                 * @return bool
                 */
                bool end();
        };
    }
}

#endif
