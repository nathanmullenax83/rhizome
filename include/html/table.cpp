#include "table.hpp"

namespace rhizome {
    namespace html {
        Table::Table() {

        }

        Table::~Table() {

        }


        void 
        Table::write_to( ostream &out, size_t indent ) const {
            string spacer(indent*4,' ');
            out << spacer << "<table>\n";
            thead.write_to(out, indent+1);
            tbody.write_to(out, indent+1);
            out << spacer << "</table>\n";
        }

        void
        Table::serialize_to( size_t level, ostream &out ) const {
            write_to(out,level);
        }
    }
}