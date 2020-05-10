#include "enumeration.hpp"

namespace rhizome {
    namespace types {
        Thing * Enumeration::clone() const {
            Enumeration *en = new Enumeration();
            for( auto i=data.begin(); i!=data.end(); i++) {
                en->data[i->first] = i->second->clone();
            }
            return en;
        }

        void Enumeration::set( Integer index, Thing *value ) {
            if( data.count(index)>0 ) {
                delete data[index];
            }
            data[index] = value;
        }

        Thing * Enumeration::get( Integer index ) {
            return data.at(index);
        }

        Thing * Enumeration::get_clone( Integer index ) const {
            return data.at(index)->clone();
        }

        string Enumeration::rhizome_type() const {
            return "Enum";
        }

        bool Enumeration::has_interface( string const &name ) {
            return name==rhizome_type() || name=="Thing";
        }

        void Enumeration::serialize_to( std::ostream &out ) const {
            out << rhizome_type() << "{";
            for( auto i=data.begin(); i!=data.end(); i++) {
                out << i->first << ":";
                i->second->serialize_to(out);
                if( i!=data.end() ) {
                    out << ";";
                }
            }
            out << "}";
        }

        Thing *
        Enumeration::invoke( string const &method, Thing *arg ) {
            (void)method;(void)arg;
            throw runtime_error("Nothing to invoke.");
        }
    }
}