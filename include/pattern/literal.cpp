#include "literal.hpp"
#include "types/string.hpp"
#include "types/bool.hpp"
#include "types/char.hpp"
#include <cassert>

using rhizome::types::String;
using rhizome::core::Dispatcher;
using rhizome::types::Bool;
using rhizome::types::Char;

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
            return name==rhizome_type()||name=="pattern"||name=="Thing";
        }

        Thing *
        Literal::invoke( Thing *context, string const &method, Thing *arg ) {
            static Dispatcher dispatcher({
                {
                    "reset!",
                    [this]( Thing *arg ) {
                        assert( arg==NULL );
                        this->reset();
                        return (Thing*)this;
                    }
                },
                {
                    "valid?",
                    [this]( Thing *arg ) {
                        assert( arg==NULL );
                        return (Thing*)new Bool(this->valid());
                    }
                },
                {
                    "accepted?",
                    [this]( Thing *arg) {
                        assert( arg==NULL );
                        return (Thing*)new Bool(this->accepted());
                    }
                },
                {
                    "can transition?",
                    [this]( Thing *arg) {
                        assert( arg!=NULL );
                        assert( arg->rhizome_type()=="Char");
                        Char *c = (Char*)arg;
                        return (Thing*)new Bool(this->can_transition(c->v));
                    }
                },
                {
                    "transition!",
                    [this](Thing *arg) {
                        assert( arg!=NULL);
                        assert( arg->rhizome_type()=="Char");
                        Char *c = (Char*)arg;
                        this->transition(c->v);
                        return (Thing*)this;
                    }
                }
            });
            try {
                Thing *r = dispatcher.at(method)(arg);
                return r;
            } catch( std::exception *e ) {
                stringstream err;
                err << "Method " << method << " is not defined on " << rhizome_type();
                if( context != NULL ) {
                    err << "\nContext: ";
                    context->serialize_to(err);
                }
                throw runtime_error(err.str());
            }
        }

        Thing *
        Literal::captured_plain() {
            //std::cout << "Captured literal: " << _captured.str() << "\n";
            return new String(_captured.str());
        }

        Thing *
        Literal::captured_transformed() {
            return captured_plain();
        }

        Literal * literal( string const &v ) {
            return new Literal(v);
        }
    }
}