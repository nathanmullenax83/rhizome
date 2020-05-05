#include "section.hpp"

namespace rhizome {
    namespace html {
        Section::Section() {

        }

        Section::~Section() {

        }

        void 
        Section::write_to( ostream &out ) {
            out << "<section>";
            write_children(out);
            out << "</section>";
        }
    }
}