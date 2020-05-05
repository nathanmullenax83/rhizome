#include "nongreedy.hpp"

namespace rhizome {
    namespace pattern {
        NonGreedy::NonGreedy( Pattern *inner ): inner(inner) {

        }

        bool
        NonGreedy::accepted() const {
            return inner->accepted();
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
            this->Pattern::reset();
        }
    }
}