#include "mapping.hpp"


#include <cassert>

namespace rhizome {
    namespace alphabet {
        Mapping::Mapping() {

        }

        void Mapping::define_map_char( wchar_t from, wchar_t to ) {
            mapping[from] = to;
        }

        void Mapping::define_map_range( wchar_t src, wchar_t dest, size_t count ) {
            for(size_t i=src; i<src+count; i++) {
                mapping[i] = dest + i;
            }
        }

        string Mapping::rhizome_type() const {
            return "alphabet::Mapping";
        }

        void Mapping::serialize_to( size_t level, std::ostream &out ) const {
            (void)level;
            out << rhizome_type();
            out << "{";
            for( auto i=mapping.begin(); i!=mapping.end(); i++) {
                out << (i->first) << ":" << (i->second);
                if( i!=mapping.end() ) {
                    out << ",";
                }
            }
            out << "}";
        }

        bool Mapping::has_interface( string const &name ) {
            return name=="Thing"||name==rhizome_type();
        }

        Thing * Mapping::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)context;
            if( method=="map") {
                assert( arg->has_interface("Tuple"));
                Tuple *t = (Tuple*)arg;
                assert( t->size()==2);
                
            } else if( method=="map_range") {
                
            }
            throw runtime_error("Reflection method not implemented!");
        }

        wchar_t Mapping::lookup( wchar_t c ) {
            if( mapping.count(c) > 0 ) {
                return mapping[c];
            } else {
                return c;
            }
        }
    }
}