#include "tbody.hpp"

namespace rhizome {
    namespace html {
        TBody::TBody() {

        }

        TBody::~TBody() {

        }

        void
        TBody::write_to( ostream &out ) {
            out << "<tbody>";
            for(size_t i=0; i<rows.size(); ++i) {
                rows[i].write_to(out);
            }
            out << "</tbody>";
        }

        void
        TBody::serialize_to( ostream &out ) const {
            out << "tbody(";
            serialize_children(out);
            out << ")";
        }

        Thing *
        TBody::clone() const {
            TBody *copy = new TBody();
            copy->children = clone_children();
            return copy;
        }


        string
        TBody::rhizome_type() const {
            return "html::TBody";
        }


    }
}