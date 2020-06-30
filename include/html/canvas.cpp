#include "canvas.hpp"

namespace rhizome {
    namespace html {
        Canvas::Canvas() {

        }

        Canvas::~Canvas() {

        }

        void
        Canvas::write_to( ostream &out, size_t indent ) {
            string spacer(indent*4,' ');
            out << spacer << open_tag("canvas") << "\n";
            out << spacer << "</canvas>\n";
        }

        string
        Canvas::rhizome_type() const {
            return "html::Canvas";
        }

        bool
        Canvas::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Thing";
        }

        Thing *
        Canvas::invoke( string const &method, Thing * arg ) {
            (void)method; (void)arg;
            throw runtime_error("No such method.");
        }
        
    }
}