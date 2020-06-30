#ifndef RHIZOME_HTML_CANVAS
#define RHIZOME_HTML_CANVAS

#include <iostream>
#include <stdexcept>
#include "element.hpp"

using std::ostream;
using std::runtime_error;

namespace rhizome {
    namespace html {
        class Canvas: public Element {
        public:
            Canvas();
            ~Canvas();

            virtual void write_to( ostream &out, size_t indent );
            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( string const &method, Thing *arg) override;
            virtual string rhizome_type() const override;
        };
    }
}

#endif