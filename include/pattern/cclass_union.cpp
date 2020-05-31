#include "cclass_union.hpp"
#include "types/string.hpp"

using rhizome::types::String;

namespace rhizome {
    namespace pattern {
        CClassUnion::CClassUnion(): state(0) {

        }

        void
        CClassUnion::add_part( CClass *c ) {
            parts.push_back(c);
        }

        void
        CClassUnion::reset() {
            state = 0;
            _valid = true;
            _captured = stringstream();
        }

        bool
        CClassUnion::can_transition(char c) const {
            bool can(false);
            if( state==1 ) return false;
            for(size_t i=0; i<parts.size(); ++i) {
                can = can || parts[i]->can_transition(c);
            }
            return can;
        }

        void
        CClassUnion::transition(char c) {
            if( can_transition(c) ) {
                _captured.put(c);
                state = 1;
                return;
            } else {
                throw runtime_error("Invalid transition!");
            }
        }

        bool
        CClassUnion::accepted() const {
            return _valid && state==1;
        }

        IPattern *
        CClassUnion::clone_pattern(bool withstate) const {
            CClassUnion *ccu = new CClassUnion();
            for(size_t i=0; i<parts.size();++i) {
                ccu->parts.push_back( (CClass*)parts[i]->clone() );
            }
            if( withstate ) {
                ccu->_valid =_valid;
                ccu->state = state;
                ccu->_captured << _captured.str();
            }
            return ccu;
            
        }

        void
        CClassUnion::serialize_to_cclass_context( ostream &out ) const {
            for(size_t i=0; i<parts.size(); ++i) {
                parts[i]->serialize_to_cclass_context(out);
            }
        }

        void
        CClassUnion::serialize_to( ostream &out ) const {
            out << "[";
            serialize_to_cclass_context(out);
            out << "]";
        }

        Thing *
        CClassUnion::captured_plain() {
            return new String(_captured.str());
        }

        Thing *
        CClassUnion::captured_transformed() {
            stringstream xd;
            for(size_t i=0; i<parts.size(); ++i) {
                Thing *t_i = parts[i]->captured_transformed();
                if( t_i != NULL ) {
                    if( t_i->rhizome_type() == "String") {
                        String *s = (String*)t_i;
                        xd << s->native_string();
                    }
                }
            }
            return new String(xd.str());
        }
    }
}