#include "div.hpp"

namespace rhizome {
    namespace html {
        Div::Div() {

        }

        Div::~Div() {

        }

        void
        Div::write_to( ostream &out, size_t indent ) const {
            string spacer(indent*4,' ');
            out << spacer << open_tag("div");
            write_children(out,indent+1);
            out << spacer << "</div>\n";
        }

        string
        Div::rhizome_type() const {
            return "html::Div";
        }

        bool
        Div::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Thing";
        }

        Thing * invoke( Thing *context, string const &method, Thing *arg ) {
            (void)arg; (void)method; (void)context;
            throw runtime_error("No such method.");
        }
    }
}