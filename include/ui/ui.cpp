#include "ui.hpp"

namespace rhizome {
    namespace ui {

        void underline( string const &s, char c ) {
            cout << s << std::endl;
            for(size_t i=0; i<s.size();++i) {
                cout << c;
            }
            cout << std::endl;
        }

        void br() {
            cout << std::endl;
        }

    }
}