#ifndef RHIZOME_UI_HPP
#define RHIZOME_UI_HPP

#include <string>
#include <iostream>

using std::string;
using std::cout;

namespace rhizome {
    namespace ui {

        /// This configuration is read from the file specified at the command line.
        class UIConfig {
        private:
            size_t web_port;
            size_t bridge_port;

        public:
            UIConfig() {

            }
        };

        
        void underline( string const &s, char c='-');
        void br();
    }
}

#endif
