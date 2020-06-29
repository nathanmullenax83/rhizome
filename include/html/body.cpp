#include "body.hpp"

namespace rhizome {
    namespace html {
        Body::Body() {

        }

        Body::~Body() {

        }

        void
        Body::write_to( ostream &out ) {
            out << "\t<body>\n";
            write_children(out);
            out << "\t</body>\n";
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

        Thing *
        Body::invoke( string const &method, Thing *arg) {
            (void)arg;
            stringstream err;
            err << "No such method: " << method;
            throw runtime_error(err.str());
        }
    }
}