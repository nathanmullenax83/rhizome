#include "alpha.hpp"

namespace rhizome {
    namespace pattern {
        Alpha::Alpha(): state(0) {

        }

        void
        Alpha::reset() {
            state = 0;
            this->Pattern::reset();
        }

        bool 
        Alpha::accepted() const {
            return state==1;
        }

        bool
        Alpha::can_transition(char c) const {
            return (state==0) && isalpha(c);
        }

        void
        Alpha::transition(char c) {
            if( can_transition(c) ) {
                ++state;
            } else {
                throw runtime_error("Alpha: cannot transition.");
            }
        }

        IPattern * 
        Alpha::clone_pattern() const {
            Alpha *c = new Alpha();
            c->state = state;
            return c;
        }

        void
        Alpha::serialize_to( ostream &out ) const {
            out << "[";
            serialize_to_cclass_context(out);
            out << "]";
        }

        void
        Alpha::serialize_to_cclass_context( ostream &out ) const {
            out << ":alpha:";
        }

        bool
        Alpha::has_interface( string const &name ) {
            return name==rhizome_type() || name=="Pattern" || name=="CClass" || name=="Thing";
        }

        string
        Alpha::rhizome_type() const {
            return "pattern::Alpha";
        }

        Thing *
        Alpha::invoke( string const &method, Thing *arg ) {
            (void)method;(void)arg;
            throw runtime_error("Nothing to invoke.");
        }
    }
}