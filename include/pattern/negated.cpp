#include "negated.hpp"

namespace rhizome {
    namespace pattern {
        Negated::Negated( CClass *inner ): inner(inner), n_accepted(0) {

        }

        Negated::~Negated() {
            delete inner;
        }

        bool 
        Negated::accepted() const {
            return n_accepted==1 && !inner->accepted();
        }

        bool
        Negated::can_transition( char c ) const {
            return n_accepted==0 && !inner->can_transition(c);
        }

        void
        Negated::transition(char c) {
            if( can_transition(c) ) {
                n_accepted++;
                return;
            } else {
                stringstream err;
                err << "Could not transition on " << /* printable */ c << ".";
                throw runtime_error(err.str());
            }
        }

        void
        Negated::reset() {
            n_accepted = 0;
            inner->reset();
            this->Pattern::reset();
        }

        Thing *
        Negated::invoke( string const &method, Thing *arg ) {
            (void)method;(void)arg;
            throw runtime_error("Nothing to invoke.");
        }
    }
}