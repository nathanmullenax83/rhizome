#include "ul.hpp"


namespace rhizome {
    namespace html {
        UL::UL() {

        }

        UL::~UL(){

        }

        void 
        UL::write_to( ostream &out ) {
            out << "<ul>";
            for(size_t i=0; i<items.size(); ++i) {
                items[i].write_to(out);
            }
            out << "</ul>";
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

        Thing * UL::invoke( string const &method, Thing *arg ) {
            (void)method; (void)arg;
            throw runtime_error("No such method.");
        }
    }

}


