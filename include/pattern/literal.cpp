#include "literal.hpp"

namespace rhizome {
    namespace pattern {
        Literal::Literal( string const &w ): w(w), state(0) {

        }

        void
        Literal::transition( char c ) {
            if( state < w.size() ) {
                if( c==w[state]) {
                    ++state;
                    return;
                } else {
                    return;
                }
            }
            return;
        }

        bool
        Literal::can_transition(char c) const {
            return valid() && (state < w.size()) && (w[state]==c);
        }

        bool
        Literal::accepted() const {
            return state==w.size();
        }

        void
        Literal::reset() {
            state = 0;
            this->Pattern::reset();
        }

        IPattern *
        Literal::clone_pattern() const {
            Literal *p = new Literal(w);
            return p;
        }

        void
        Literal::serialize_to( ostream &out ) const {
            out << w;
        }

        string
        Literal::rhizome_type() const {
            return "pattern::Literal";
        }

        bool
        Literal::has_interface(string const &name ) {
            return name==rhizome_type()||name=="Pattern"||name=="Thing";
        }

        Thing *
        Literal::invoke( string const &method, Thing *arg ) {
            (void)method;(void)arg;
            throw runtime_error("Nothing to invoke.");
        }
    }
}