#include "body.hpp"

namespace rhizome {
    namespace html {
        Body::Body() {

        }

        Body::~Body() {

        }

        void
        Body::write_to( ostream &out, size_t indent ) {
            string spacer( indent*4, ' ');
            out << spacer << "<body>\n";
            write_children(out,indent+1);
            out << spacer << "</body>\n";
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
        Body::invoke( Thing *context, string const &method, Thing *arg) {
            (void)arg; (void)context;
            stringstream err;
            err << "No such method: " << method;
            throw runtime_error(err.str());
        }
    }
}