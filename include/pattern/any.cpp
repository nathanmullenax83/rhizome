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
            return _valid && state==1;
        }

        bool Any::can_transition(char c) const {
            (void)c;
            return state==0;
        }


        void 
        Any::transition(char c) {
            if( can_transition(c)) {
                _captured.put(c);
                ++state; return;
            } else {
                throw runtime_error("Couldn't transition!");
            }
        }

        void Any::serialize_to( size_t level, ostream &out ) const {
            (void)level;
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
        Any::invoke( Thing * context, string const &method, Thing *arg ) {
            (void)method;(void)arg;(void)context;
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

        string
        Any::rhizome_type() const {
            return "AnyChar";
        }

        bool
        Any::has_interface( string const &name ) {
            return name=="Thing"||name=="pattern"||name==rhizome_type();
        }


    }
}