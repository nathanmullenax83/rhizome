#include "body.hpp"

namespace rhizome {
    namespace html {
        Body::Body() {

        }

        Body::~Body() {

        }

        void
        Body::write_to( ostream &out ) {
            out << "<body>";
            write_children(out);
            out << "</body>";
        }

        void
        Body::serialize_to( ostream &out ) const {
            out << "body(";
            serialize_children(out);
            out << ")";
        }

 

        Thing * 
        Body::clone() const {
            Body *b = new Body();
            b->children = clone_children();
            return b;
        }

        string
        Body::rhizome_type() const {
            return "html::Body";
        }

        bool
        Body::has_interface( string const &name ) {
            return (name==rhizome_type()||name=="Thing");
        }
    }
}