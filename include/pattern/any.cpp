#include "any.hpp"

namespace rhizome {
    namespace pattern {
        Any::Any(): state(0) {

        }

        Any::~Any() {

        }

        void Any::reset() {
            state = 0;
            this->Pattern::reset();
        }

        bool Any::accepted() const {
            return state==1;
        }
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
        bool Any::can_transition(char c) const {
            return state==0;
        }
#pragma GCC diagnostic pop

        void 
        Any::transition(char c) {
            if( can_transition(c)) {
                ++state; return;
            } else {
                throw runtime_error("Couldn't transition!");
            }
        }

        void Any::serialize_to( ostream &out ) const {
            out << ".";
        }

        void Any::serialize_to_cclass_context( ostream &out ) const {
            out << ":print::cntrl:";
        }

        IPattern *
        Any::clone_pattern() const {
            rp::Any *p = new rp::Any();
            p->state = state;
            return p;
        }
    }
}