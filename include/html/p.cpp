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
        P::write_to( ostream &out ) {
            out << "<p>";
            write_children(out);
            out << "</p>";
        }

    }
}