#include "range.hpp"
#include "types/string.hpp"

using rhizome::types::String;

namespace rhizome {
    namespace pattern {
        Range::Range( char from, char to ): from(from), to(to), state(0) {

        }

        bool
        Range::accepted() const {
            return state==1;
        }

        void
        Range::transition(char c) {
            if( c>=from && c<=to && state==0) {
                state = 1;
            } 
        }

        bool
        Range::can_transition(char c) const {
            return state==0
                && (from <= c && c <= to);
        }

        void
        Range::reset() {
            state = 0;
            _valid = true;
            _captured = stringstream();
        }

        IPattern * 
        Range::clone_pattern(bool withstate) const {
            Range *p = new Range(from,to);
            if( withstate ) {
                p->state = state;
                p->_valid = _valid;
                p->_captured << _captured.str();
            }
            return p;
        }

        void
        Range::serialize_to_cclass_context( ostream &out ) const {
            out << from << "-" << to;
        }

        void 
        Range::serialize_to( ostream &out ) const {
            out << "[";
            serialize_to_cclass_context(out);
            out << "]";
        }

        bool
        Range::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Pattern"||name=="CClass"||name=="Thing";
        }

        Thing *
        Range::invoke( string const &method, Thing *arg ) {
            (void)method;(void)arg;
            throw runtime_error("Nothing to invoke.");
        }

        string
        Range::rhizome_type() const {
            return "pattern::Range";
        }

        Thing *
        Range::captured_plain() {
            if( accepted() ) {
                stringstream s;
                serialize_to(s);
                return new String(s.str());
            } else {
                return new String();
            }
        }

        Thing *
        Range::captured_transformed() {
            return captured_plain();
        }
    }
}