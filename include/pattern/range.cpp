#include "range.hpp"

namespace rhizome {
    namespace pattern {
        Range::Range( char from, char to ): from(from), to(to), state(0) {

        }

        bool
        Range::accepted() const {
            return state==1;
        }

        void
        Range::transition(char c) {
            if( c>=from && c<=to && state==0) {
                state = 1;
            } 
        }

        bool
        Range::can_transition(char c) const {
            return state==0
                && (from <= c && c <= to);
        }

        void
        Range::reset() {
            state = 0;
            this->Pattern::reset();
        }

        IPattern * 
        Range::clone_pattern() const {
            Range *p = new Range(from,to);
            p->state = state;
            return p;
        }

        void
        Range::serialize_to_cclass_context( ostream &out ) const {
            out << from << "-" << to;
        }

        void 
        Range::serialize_to( ostream &out ) const {
            out << "[";
            serialize_to_cclass_context(out);
            out << "]";
        }

        bool
        Range::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Pattern"||name=="CClass"||name=="Thing";
        }

        Thing *
        Range::invoke( string const &method, Thing *arg ) {
            (void)method;(void)arg;
            throw runtime_error("Nothing to invoke.");
        }
    }
}