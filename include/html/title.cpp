#include "title.hpp"

namespace rhizome {
    namespace html {
        Title::Title(): cdata("") {

        }

        Title::Title( string const &cdata ): cdata(cdata) {

        }

        Title::~Title() {

        }

        void
        Title::write_to( ostream &out ) {
            out << "<title>";
            out << cdata;
            out << "</title>";
        }

        void
        Title::serialize_to( ostream &out ) const {
            out << rhizome_type() << "(\"";
            out << cdata;
            out << "\")";
        }

        Thing * 
        Title::clone() const {
            return new Title(cdata);
        }

        string
        Title::rhizome_type() const {
            return "html::Title";
        }

        Thing * Title::invoke( string const &method, Thing *arg ) {
            (void) arg;
            stringstream ss;
            ss << "No such method: " << method;
            throw runtime_error(ss.str());
        }
    }
}