#include "chars.hpp"

namespace rhizome {
    namespace pattern {
        Chars::Chars(): state(0) {
            
        }

        Chars::Chars( string const &cees ): state(0) {
            for( size_t i=0; i<cees.size(); ++i) {
                cs.emplace( cees[i]);
            }
        }

        string Chars::rhizome_type() const {
            return "pattern::Chars";
        }

        bool Chars::has_interface( string const &w ) {
            return w==rhizome_type()||w=="Pattern"||w=="Thing";
        }

        void Chars::serialize_to( std::ostream &out ) const {
            out << "[";
            for( auto i=cs.begin(); i!=cs.end(); i++) {
                out << (*i);
            }
            out << "]";
        }

        void Chars::serialize_to_cclass_context( std::ostream &out ) const {
            for( auto i=cs.begin(); i!=cs.end(); i++) {
                out << (*i);
            }
        }

        IPattern * Chars::clone_pattern() const {
            Chars *copy = new Chars();
            copy->cs = cs;
            return copy;
        }

        bool Chars::can_transition( char c ) const {
            return state==0 && (cs.count(c) > 0);
        }

        void Chars::transition( char c ) {
            assert( state==0 && cs.count(c)>0);

        }

        bool Chars::accepted() const {
            return state==1;
        }
    }
}