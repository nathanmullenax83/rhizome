#include "td.hpp"

namespace rhizome {
    namespace html {
        Td::Td() {

        }

        Td::~Td() {

        }

        void
        Td::write_to( ostream &out, size_t indent ) const {
            string spacer(indent*4,' ');
            out << spacer << "<td>";
            write_children(out, indent+1);
            out << spacer << "</td>";
        }
    }
}