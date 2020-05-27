#include "system.hpp"

namespace rhizome {
    namespace core {
        System::System(IParser *parser, IStore *store): parser(parser), store(store) {
            
        }

        System::~System() {
            delete parser;
            delete store;
        }

        string
        System::rhizome_type() const {
            return "System";
        }

        void 
        System::serialize_to( std::ostream &out ) const {
            out << rhizome_type() << "{";
            out << "}";
        }

        Thing *
        System::clone() const {
            Thing *unsafe = (Thing*)parser;
            IParser *parser_clone = (IParser*) unsafe->clone();
            Thing *unsafe_store = (Thing*)store;
            IStore *store_clone = (IStore*)unsafe_store->clone();
            System *copy = new System(parser_clone,store_clone);
            return copy;
        }

        bool
        System::has_interface( string const &name ) {
            return name==rhizome_type() || name=="Thing";
        }

        Thing *
        System::invoke( string const &method, Thing *arg ) {
            if( arg==NULL ) {
                if( method=="clone" ) {
                    return clone();
                } else if( method=="type" ) {
                    
                } else if( method=="parse") {
                    stringstream ss;
                    arg->serialize_to(ss);
                    return parser->parse_thing( ss.str() );
                }
            }
            throw runtime_error("Not implemented.");
        }
        
    }
}