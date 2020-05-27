#include "pattern.hpp"
#include "types/string.hpp"
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

        

        bool
        Pattern::accepts( string const &w ) {
            this->reset();
            for(size_t i=0; i<w.size();++i) {
                if( can_transition(w[i])) {
                    transition(w[i]);
                } else {
                    return false;
                }
            }
            bool a = accepted();
            return a;
        }

        Thing *
        Pattern::clone() const {
            return (Thing*)clone_pattern(true);
        }

        
        
    }
}