#include "div.hpp"

namespace rhizome {
    namespace html {
        Div::Div() {

        }

        Div::~Div() {

        }

        void
        Div::write_to( ostream &out ) {
            out << "<div>";
            write_children(out);
            out << "</div>";
        }

        string
        Div::rhizome_type() const {
            return "html::Div";
        }

        bool
        Div::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Thing";
        }
    }
}