#include "pattern.hpp"

namespace rhizome {
    namespace pattern {

        Pattern::Pattern(): _valid(true) {

        }

        Pattern::~Pattern() {
            
        }

        void
        Pattern::invalidate() {
            _valid = false;
        }

        bool
        Pattern::valid() const {
            return _valid;
        }

        void
        Pattern::reset() {
            _valid = true;
        }

        bool
        Pattern::accepts( string const &w ) {
            reset();
            for(size_t i=0; i<w.size();++i) {
                if( can_transition(w[i])) {
                    transition(w[i]);
                } else {
                    reset();
                    return false;
                }
            }
            bool a = accepted();
            reset();
            return a;
        }

        Thing *
        Pattern::clone() const {
            return (Thing*)clone_pattern();
        }

    }
}