#include "p.hpp"

namespace rhizome {
    namespace html {
        P::P(): cdata("") {

        }

        P::P(string const &cdata): cdata(cdata) {

        }

        P::~P() {
            
        }

        void 
        P::write_to( ostream &out, size_t indent ) {
            string spacer(indent*4,' ');
            out << spacer << "<p>";
            out << cdata;
            out << "</p>\n";
        }

    }
}