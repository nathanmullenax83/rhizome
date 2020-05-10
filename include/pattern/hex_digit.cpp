#include "hex_digit.hpp"

namespace rhizome {
    namespace pattern {
        HexDigit::HexDigit(): state(0) {

        }

        HexDigit::~HexDigit() {

        }

        void
        HexDigit::reset() {
            state = 0;
            this->Pattern::reset();
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
            return state==1;
        }

        IPattern *
        HexDigit::clone_pattern() const {
            HexDigit *p = new HexDigit();
            p->state = state;
            return p;
        }

        void
        HexDigit::serialize_to_cclass_context( ostream &out ) const {
            out << ":xdigit:";
        }

        void
        HexDigit::serialize_to( ostream &out ) const {
            out << "[";
            serialize_to_cclass_context(out);
            out << "]";
        }

        Thing *
        HexDigit::invoke( string const &method, Thing *arg ) {
            (void)method;(void)arg;
            throw runtime_error("Nothing to invoke.");
        }
    }
}