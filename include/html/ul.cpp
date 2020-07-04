#include "ul.hpp"


namespace rhizome {
    namespace html {
        UL::UL() {

        }

        UL::~UL(){

        }

        void 
        UL::write_to( ostream &out, size_t indent ) {
            string spacer(indent*4,' ');
            out << spacer << "<ul>\n";
            for(size_t i=0; i<items.size(); ++i) {
                items[i].write_to(out,indent+1);
            }
            out << spacer << "</ul>\n";
        }

        void
        UL::serialize_to( ostream &out ) const {
            out << rhizome_type() << "(";
            for(size_t i=0; i<items.size(); ++i) {
                items[i].serialize_to(out);
            }
            out << ")";
        }

        LI &
        UL::li( string const &content ) {
            items.push_back( LI(content) );
            return items.back();
        }

        Thing *
        UL::clone() const {
            UL *list = new UL();
            for(size_t i=0; i<items.size();++i) {
                list->items.push_back( *((LI*)items[i].clone()) );
            }
            return list;
        }

        string
        UL::rhizome_type() const {
            return "html::UL";
        }

        Thing * UL::invoke(Thing *context, string const &method, Thing *arg ) {
            (void)method; (void)arg; (void)context;
            throw runtime_error("No such method.");
        }
    }

}


