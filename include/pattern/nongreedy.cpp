#include "nongreedy.hpp"

namespace rhizome {
    namespace pattern {
        NonGreedy::NonGreedy( Pattern *inner ): inner(inner) {

        }

        bool
        NonGreedy::accepted() const {
            return _valid && inner->accepted();
        }

        bool
        NonGreedy::can_transition(char c) const {
            if( accepted() ) return false;
            return inner->can_transition(c);
        }

        void
        NonGreedy::transition(char c) {
            return inner->transition(c);
        }

        void
        NonGreedy::reset() {
            inner->reset();
            _valid = true;
            _captured = stringstream();
        }

        Thing *
        NonGreedy::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)method;(void)arg; (void)context;
            throw runtime_error("Nothing to invoke.");
        }

        
    }
}