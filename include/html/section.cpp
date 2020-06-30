#include "section.hpp"

namespace rhizome {
    namespace html {
        Section::Section() {

        }

        Section::~Section() {

        }

        void 
        Section::write_to( ostream &out, size_t indent ) {
            string spacer(indent*4,' ');
            out << spacer << "<section>\n";
            write_children(out,indent+1);
            out << spacer << "</section>\n";
        }
    }
}