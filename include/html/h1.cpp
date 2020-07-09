#include "h1.hpp"

namespace rhizome {
    namespace html {
        H1::H1() {

        }

        H1::H1(string const &title): title(title) {

        }

        H1::~H1() {

        }

        void
        H1::write_to( ostream &out, size_t indent ) const {
            string spacer(indent*4,' ');
            out << spacer << "<h1>" << title << "</h1>\n";
        }

        void
        H1::serialize_to( size_t level, ostream &out ) const {
            write_to(out,level);
        }

        Thing *
        H1::clone() const {
            return new H1(title);
        }

        string
        H1::rhizome_type() const {
            return "html::H1";
        }

        bool
        H1::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Thing";
        }

        Thing *
        H1::invoke( Thing *context, string const &method, Thing *arg ) {
            (void) method; (void)arg; (void)context;
            throw runtime_error("No such method.");
        }
    }
}