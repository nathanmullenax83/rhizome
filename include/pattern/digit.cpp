#include "digit.hpp"

#include "types/string.hpp"

using rhizome::types::String;
using rhizome::core::Dispatcher;

namespace rhizome {
    namespace pattern {
        Digit::Digit(): state(0) {

        }

        Digit::~Digit() {

        }

        IPattern * 
        Digit::clone_pattern(bool withstate) const {
            Digit *clone = new Digit();
            if( withstate ) {
                clone->state = state;
                clone->_valid =_valid;
                clone->_captured << _captured.str();
            }
            return clone;
        }

        bool
        Digit::accepted() const {
            return _valid && state==1;
        }

        bool
        Digit::can_transition(char c) const {
            return state==0 && isdigit(c);
        }

        void
        Digit::transition(char c) {
            if( can_transition(c) ) {
                _captured.put(c);
                ++state;
                return;
            }
            throw runtime_error("Digit pattern could not accept");
        }

        void
        Digit::reset() {
            state = 0;
            _valid = true;
            _captured = stringstream();
        }

        void
        Digit::serialize_to_cclass_context( ostream &out ) const {
            out << "⁹";
        }

        string
        Digit::rhizome_type() const {
            return "pattern::Digit";
        }

        bool
        Digit::has_interface( string const &name )  {
            return name==rhizome_type()||name=="Pattern"||name=="CClass"||name=="Thing";
        }

        void
        Digit::serialize_to( size_t level, ostream &out ) const {
            (void)level;
            serialize_to_cclass_context(out);
        }

        Thing *
        Digit::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)method;(void)arg;(void)context;
            throw runtime_error("Nothing to invoke.");
        }

        Thing *
        Digit::captured_plain() {
            return new String(_captured.str());
        }

        Thing *
        Digit::captured_transformed() {
            return captured_plain();
        }
    }
}