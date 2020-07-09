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
        Title::write_to( ostream &out, size_t indent ) const {
            string spacer(indent*4,' ');
            out << spacer << "<title>" << cdata << "</title>\n";
        }

        void
        Title::serialize_to( size_t level, ostream &out ) const {
            write_to(out,level);
        }

        Thing * 
        Title::clone() const {
            return new Title(cdata);
        }

        string
        Title::rhizome_type() const {
            return "html::Title";
        }

        Thing * Title::invoke(Thing *context,  string const &method, Thing *arg ) {
            (void) arg; (void)context;
            stringstream ss;
            ss << "No such method: " << method;
            throw runtime_error(ss.str());
        }
    }
}