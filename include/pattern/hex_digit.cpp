#include "hex_digit.hpp"

#include "types/string.hpp"

using rhizome::types::String;

namespace rhizome {
    namespace pattern {
        HexDigit::HexDigit(): state(0) {

        }

        HexDigit::~HexDigit() {

        }

        void
        HexDigit::reset() {
            state = 0;
            _valid = true;
            _captured = stringstream();
        }

        bool
        HexDigit::can_transition(char c) const {
            return state==0 && (  
                isdigit(c)
             || (c >= 'a' && c <= 'f')
             || (c >= 'A' && c <= 'F')
            );
        }

        void
        HexDigit::transition(char c) {
            if( can_transition(c)) {
                state = 1;
                return;
            } else {
                throw runtime_error("HexDigit: Cannot transition.");
            }
        }

        bool
        HexDigit::accepted() const {
            return _valid && state==1;
        }

        IPattern *
        HexDigit::clone_pattern(bool withstate) const {
            HexDigit *p = new HexDigit();
            if( withstate) {
                p->state = state;
                p->_captured << _captured.str();
                p->_valid = _valid;
            }
            return p;
        }

        void
        HexDigit::serialize_to_cclass_context( ostream &out ) const {
            out << "⑯";
        }

        void
        HexDigit::serialize_to( size_t level, ostream &out ) const {
            (void)level;
            out << "[";
            serialize_to_cclass_context(out);
            out << "]";
        }

        Thing *
        HexDigit::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)method;(void)arg;(void)context;
            throw runtime_error("Nothing to invoke.");
        }

        string
        HexDigit::rhizome_type() const {
            return "cclass::HexDigit";
        }

        bool
        HexDigit::has_interface( string const &name ) {
            return name==rhizome_type() || name=="cclass" || name=="Thing";
        }

        Thing *
        HexDigit::captured_plain() {
            if( accepted()) {
                stringstream s;
                serialize_to(0,s);
                return new String(s.str());
            } else {
                return new String("");
            }
        }

        Thing *
        HexDigit::captured_transformed() {
            return captured_plain();
        }
    }
}