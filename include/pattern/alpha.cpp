#include "alpha.hpp"

#include "types/string.hpp"

using rhizome::types::String;

namespace rhizome {
    namespace pattern {
        Alpha::Alpha(): state(0) {

        }

        void
        Alpha::reset() {
            state = 0;
            _valid = true;
            _captured = stringstream();
        }

        bool 
        Alpha::accepted() const {
            return _valid && state==1;
        }

        bool
        Alpha::can_transition(char c) const {
            return (state==0) && isalpha(c);
        }

        void
        Alpha::transition(char c) {
            if( can_transition(c) ) {
                ++state;
                _captured.put(c);
            } else {
                throw runtime_error("Alpha: cannot transition.");
            }
        }

        IPattern * 
        Alpha::clone_pattern(bool withstate) const {
            Alpha *a = new Alpha();
            if( withstate ) {
                a->_captured << _captured.str();
                a->state = state;
                a->_valid = _valid;
            }
            return a;
        }

        void
        Alpha::serialize_to( size_t level, ostream &out ) const {
            (void)level;
            out << "[";
            serialize_to_cclass_context(out);
            out << "]";
        }

        void
        Alpha::serialize_to_cclass_context( ostream &out ) const {
            out << "α";
        }

        bool
        Alpha::has_interface( string const &name ) {
            return name==rhizome_type() || name=="Pattern" || name=="CClass" || name=="Thing";
        }

        string
        Alpha::rhizome_type() const {
            return "pattern::Alpha";
        }

        Thing *
        Alpha::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)method;(void)arg; (void)context;
            throw runtime_error("Nothing to invoke.");
        }

        Thing *
        Alpha::captured_plain() {
            Thing *s = new String(_captured.str());
            reset();
            return s;
        }

        Thing *
        Alpha::captured_transformed() {
            return captured_plain();
        }
    }
}