#ifndef RHIZOME_HTML_P_HPP
#define RHIZOME_HTML_P_HPP

#include <iostream>
#include <string>
#include "pattern.hpp"
#include "element.hpp"
#include "container.hpp"

using std::ostream;
using std::string;
using rhizome::pattern::Pattern;

using rhizome::html::Container;


namespace rhizome {
    namespace html {
        class P: public Container {
        private:
            string cdata;
        public:
            P();
            P(string const &cdata);
            ~P();

            virtual void write_to( ostream &out, size_t indent );

            // virtual Pattern * make_pattern();
            // virtual Pattern * make_concise_pattern();
        };
    }
}

#endif