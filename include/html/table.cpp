#include "table.hpp"

namespace rhizome {
    namespace html {
        Table::Table() {

        }

        Table::~Table() {

        }


        void 
        Table::write_to( ostream &out ) {
            out << "<table>";
            thead.write_to(out);
            tbody.write_to(out);
            out << "</table>";
        }

        void
        Table::serialize_to( ostream &out ) const {
            out << "table(";
            thead.serialize_to(out);
            tbody.serialize_to(out);
            out << ")";
        }
    }
}