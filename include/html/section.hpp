#ifndef RHIZOME_HTML_SECTION_HPP
#define RHIZOME_HTML_SECTION_HPP

#include <iostream>
#include "element.hpp"
#include "container.hpp"


namespace rhizome {
    namespace html {
        class Section: public Element, public Container {
        public:
            Section();
            ~Section();

            virtual void write_to( ostream &out );
        };
    }
}

#endif