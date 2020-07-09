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
        LI::write_to( ostream &out, size_t indent )  const{
            string spacer(indent*4,' ');
            out << spacer << "<li>" << cdata << "</li>\n";
        }

        void
        LI::serialize_to(size_t level, ostream &out) const {
            write_to(out,level);
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

        Thing *
        LI::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)method; (void)arg; (void)context;
            throw runtime_error("I'm unfamiliar with that method.");
        }
    }
}