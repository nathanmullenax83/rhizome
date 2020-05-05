#ifndef RHIZOME_HTML_CANVAS
#define RHIZOME_HTML_CANVAS

#include <iostream>
#include "element.hpp"

using std::ostream;

namespace rhizome {
    namespace html {
        class Canvas: public Element {
        public:
            Canvas();
            ~Canvas();

            virtual void write_to( ostream &out );
            virtual bool has_interface( string const &name ) override;
            virtual string rhizome_type() const override;
        };
    }
}

#endif