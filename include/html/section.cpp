#include "section.hpp"
using rhizome::core::indent;

namespace rhizome {
    namespace html {
        Section::Section() {

        }

        Section::~Section() {

        }

        void 
        Section::write_to( ostream &out, size_t level ) const {
            out << indent(level) << "<section>\n";
            write_children(out,level+1);
            out << indent(level) << "</section>\n";
        }
    }
}