#ifndef RHIZOME_HTML_DIV
#define RHIZOME_HTML_DIV

#include <iostream>

using std::ostream;


#include "element.hpp"
#include "container.hpp"

namespace rhizome {
    namespace html {
        class Div: public Element, Container {
        public:
            Div();
            ~Div();

            virtual void write_to( ostream &out );
            virtual bool has_interface( string const &name ) override;
            virtual string rhizome_type() const override;
        };
    }
}

#endif