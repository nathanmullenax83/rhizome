#include "alphabet_demo.hpp"

#include <cwchar>
#include <sstream>
#include <string>

using rhizome::ui::Console;
using rhizome::core::FreeList;

namespace rhizome {
    namespace demo {
        void alphabet_demo() {
            FreeList pointers;

            Console console(std::cout,1,1,60,20);

            Classifier *c = rhizome::alphabet::create_rhizome_classifier();
            pointers += c;

            
            console
                .h1("Character classification test.")
                .para("The Classifier object is for classifying wide characters. "
                    "Just embed whatever functions you need to categorize characters "
                    "for your lexical phase. ");
            
            std::wstring test(L"Classify (this)!");

            for(size_t i=0; i<test.size(); ++i) {
                wchar_t w = test[i];
                std::set<string> cs = c->classes(test[i]);
                console << "    ";
                std::cout << rhizome::ui::FG_GREEN_ON;
                std::wcout << w;
                std::cout << rhizome::ui::RESET_COLOR;
                    std::wcout << L"\t";
                for(auto i=cs.begin(); i!=cs.end();i++){
                    
                    std::cout << *i << " ";
                }
                std::cout << "\n";
            }

            console
                .para("Press any key to return to the main menu.");

            console.termios_getch(false);
            console.termios_getch(false);
        }
    }
}