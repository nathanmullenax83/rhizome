#include "tr.hpp"

namespace rhizome {
    namespace html {
        Tr::Tr() {

        }

        Tr::~Tr() {

        }

        void
        Tr::write_to( ostream &out, size_t indent ) const {
            string spacer(indent*4,' ');
            out << spacer << "<tr>\n";
            for(size_t i=0; i<cells.size(); ++i) {
                cells.at(i).write_to(out,indent+1);
            }
            out << spacer << "</tr>\n";
        }

        void
        Tr::serialize_to( size_t level, std::ostream &out ) const {
            write_to(out,level);
        }

        Thing * 
        Tr::clone() const {
            Tr * tr = new Tr();
            tr->children = clone_children();
            return tr;
        }


        string
        Tr::rhizome_type() const {
            return "html::Tr";
        }

        Thing *
        Tr::invoke( Thing *context, string const &method, Thing *arg) {
            (void)context;
            (void)method;
            (void)arg;
            throw runtime_error("Not implemented.");
        }

        
    }
}