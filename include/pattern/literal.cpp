#include "literal.hpp"
#include "types/string.hpp"



using rhizome::types::String;

namespace rhizome {
    namespace pattern {


        Literal::Literal( string const &w ): w(w), state(0) {

        }

        void
        Literal::transition( char c ) {
            if( state < w.size() ) {
                if( c==w[state]) {
                    ++state;
                    _captured.put(c);
                    return;
                } else {
                    stringstream err;
                    err << "'"; err.put(c); err << "' is not a valid transition for the pattern ";
                    serialize_to(err);
                    err << " state = " << state << "; _captured = " << _captured.str();
                    throw runtime_error(err.str());
                }
            } else {
                stringstream err;
                err << "Too many characters! ";
                err << " state = " << state << "; _captured = " << _captured.str();
                err << " character = '";
                err.put(c);
                err << "'";
                throw runtime_error(err.str());
            }
        }

        bool
        Literal::can_transition(char c) const {
            return valid() && (state < w.size()) && (w[state]==c);
        }

        bool
        Literal::accepted() const {
            return _valid && state==w.size();
        }

        void
        Literal::reset() {
            //std::cout << "Literal reset (" << w << ").\n";
            state = 0;
            _valid = true;
            _captured = stringstream();
        }

        IPattern *
        Literal::clone_pattern(bool withstate) const {
            Literal *p = new Literal(w);
            if( withstate ) {
                p->_valid = _valid;
                p->_captured << _captured.str();
                p->state = state;
            }
            return p;
        }

        void
        Literal::serialize_to( ostream &out ) const {
            out << "«" << w << "»";
        }

        string
        Literal::rhizome_type() const {
            return "pattern::Literal";
        }

        bool
        Literal::has_interface(string const &name ) {
            return name==rhizome_type()||name=="Pattern"||name=="Thing";
        }

        Thing *
        Literal::invoke( string const &method, Thing *arg ) {
            (void)method;(void)arg;
            throw runtime_error("Nothing to invoke.");
        }

        Thing *
        Literal::captured_plain() {
            //std::cout << "Captured literal: " << _captured.str() << "\n";
            return new String(_captured.str());
        }

        Thing *
        Literal::captured_transformed() {
            Thing *c = captured_plain();
            //std::cout << "Literal captured: ";
            //c->serialize_to(std::cout);
            //std::cout << "\n";
            return c;
        }

        Literal * literal( string const &v ) {
            return new Literal(v);
        }
    }
}