#include "li.hpp"

namespace rhizome {
    namespace html {
        LI::LI() {

        }

        LI::LI(string const &cdata): cdata(cdata) {

        }

        LI::~LI() {

        }

        void
        LI::write_to( ostream &out ) {
            out << "<li>";
            out << cdata;
            out << "</li>";
        }

        void
        LI::serialize_to(ostream &out) const {
            out << "li(\"";
            out << cdata;
            out << "\")";
        }

        Thing *
        LI::clone() const {
            return new LI(cdata);
        }

        string
        LI::rhizome_type() const {
            return "html::LI";
        }

        bool
        LI::has_interface( string const &name ) {
            return (name==rhizome_type()||name=="Thing");
        }
    }
}