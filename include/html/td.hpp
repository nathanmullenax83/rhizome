#ifndef RHIZOME_HTML_TD_HPP
#define RHIZOME_HTML_TD_HPP

#include <iostream>
#include "element.hpp"
#include "container.hpp"

using std::ostream;

namespace rhizome {
    namespace html {
        class Td: public Element, public Container {
        public:
            Td();
            ~Td();

            virtual void write_to( ostream &out, size_t indent );
        };
    }
}

#endif