#include "element.hpp"
#include "log.hpp"

namespace rhizome {
    namespace html {
        Element::~Element() {
            
        }

        string &
        Element::operator[]( string const &attr ) {
            // should be validated!
            return attributes[attr];
        }

        bool
        Element::has_interface( string const &name ) {
            return name==rhizome_type();
        }
    }
}