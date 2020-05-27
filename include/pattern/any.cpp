#include "any.hpp"
#include "types/string.hpp"

using rhizome::types::String;

namespace rhizome {
    namespace pattern {
        Any::Any(): state(0) {

        }

        Any::~Any() {

        }

        void Any::reset() {
            state = 0;
            _captured = stringstream();
            _valid = true;
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
                _captured.put(c);
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
        Any::clone_pattern(bool withstate) const {
            rp::Any *p = new rp::Any();
            if( withstate ) {
                p->state = state;
                p->_captured << _captured.str();
                p->_valid = _valid;
            }
            return p;
        }

        Thing *
        Any::invoke( string const &method, Thing *arg ) {
            (void)method;(void)arg;
            throw runtime_error("Nothing to invoke.");
        }

        Thing *
        Any::captured_plain() {
            return new String(_captured.str());
        }

        Thing *
        Any::captured_transformed() {
            return captured_plain();
        }
    }
}