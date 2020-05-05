#include "canvas.hpp"

namespace rhizome {
    namespace html {
        Canvas::Canvas() {

        }

        Canvas::~Canvas() {

        }

        void
        Canvas::write_to( ostream &out ) {
            out << "<canvas>";
            out << "</canvas>";
        }

        string
        Canvas::rhizome_type() const {
            return "html::Canvas";
        }

        bool
        Canvas::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Thing";
        }
        
    }
}