#include "tbody.hpp"

namespace rhizome {
    namespace html {
        TBody::TBody() {

        }

        TBody::~TBody() {

        }

        void
        TBody::write_to( ostream &out, size_t indent ) const{
            string spacer(indent*4,' ');
            out << spacer << "<tbody>\n";
            for(size_t i=0; i<rows.size(); ++i) {
                rows[i].write_to(out,indent+1);
            }
            out << spacer << "</tbody>\n";
        }

        void
        TBody::serialize_to( size_t level, ostream &out ) const {
            write_to(out,level);
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

        Thing *
        TBody::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)context;
            (void)method;
            (void)arg;
            throw runtime_error("Not implemented.");
        }

    }
}