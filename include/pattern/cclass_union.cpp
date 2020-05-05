#include "cclass_union.hpp"

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
            this->Pattern::reset();
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
                state = 1;
                return;
            } else {
                throw runtime_error("Invalid transition!");
            }
        }

        bool
        CClassUnion::accepted() const {
            return state==1;
        }

        IPattern *
        CClassUnion::clone_pattern() const {
            CClassUnion *ccu = new CClassUnion();
            for(size_t i=0; i<parts.size();++i) {
                ccu->parts.push_back( (CClass*)parts[i]->clone() );
            }
            ccu->state = state;
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
    }
}