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
        H1::write_to( ostream &out ) {
            out << "<h1>";
            out << title;
            out << "</h1>";
        }

        void
        H1::serialize_to( ostream &out ) const {
            out << rhizome_type() << "(\"";
            out << title;
            out << "\")";
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
    }
}