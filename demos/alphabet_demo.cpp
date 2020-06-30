#include "alphabet_demo.hpp"

#include <cwchar>
#include <sstream>
#include <string>

using rhizome::ui::Console;

namespace rhizome {
    namespace demo {
        void alphabet_demo() {
            Console console(std::cout);

            Classifier *c = rhizome::alphabet::create_rhizome_classifier();
            console.h1("Character classification test.");
            std::wstring test(L"This is an alphabet classification test. Test();");
            for(size_t i=0; i<test.size(); ++i) {
                wchar_t w = test[i];
                std::set<string> cs = c->classes(test[i]);
                std::cout << rhizome::ui::FG_GREEN_ON;
                std::wcout << w;
                std::cout << rhizome::ui::RESET_COLOR;
                    std::wcout << L"\t";
                for(auto i=cs.begin(); i!=cs.end();i++){
                    
                    std::cout << *i << " ";
                }
                std::cout << "\n";
            }
            console.termios_getch(false);
            console.termios_getch(false);

        }
    }
}