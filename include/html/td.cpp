#include "td.hpp"

namespace rhizome {
    namespace html {
        Td::Td() {

        }

        Td::~Td() {

        }

        void
        Td::write_to( ostream &out ) {
            out << "<td>";
            write_children(out);
            out << "</td>";
        }
    }
}