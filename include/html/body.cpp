#include "body.hpp"

using rhizome::core::indent;

namespace rhizome {
    namespace html {
        Body::Body() {

        }

        Body::~Body() {

        }

        void
        Body::write_to( ostream &out, size_t level ) const {
            out << indent(level) << "<body>\n";
            write_children(out,level+1);
            out << indent(level) << "</body>\n";
        }

        void
        Body::serialize_to( size_t level, ostream &out ) const {
            write_to(out,level);
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