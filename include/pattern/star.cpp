#include "star.hpp"
#include "types/string.hpp"
using rhizome::types::String;

namespace rhizome {
    namespace pattern {
        Star::Star( IPattern *inner ): inner(inner) {

        }

        Star::~Star() {
            delete inner;
        }

        bool
        Star::accepted() const {
            return _valid && true;
        }

        void
        Star::transition(char c) {
            if( inner->can_transition(c) ) {
                inner->transition(c);
                _captured.put(c);
                if( inner->accepted() ) {
                    Thing *token = inner->captured_transformed();
                    if( token != NULL && token->rhizome_type()=="String") {
                        String *s = (String*)token;
                        xd << s->native_string();
                    }
                    inner->reset();
                }
                return;
            } else if( inner->accepted() ) {
                match_count++;
                // got a match: get transformed token
                Thing *token = inner->captured_transformed();
                if( token != NULL && token->rhizome_type()=="String") {
                    String *s = (String*)token;
                    xd << s->native_string();
                }
                inner->reset();
                inner->transition(c);
                _captured.put(c);
                return;
            } else {
                throw runtime_error("Star: bad transition.");
            }
        }

        bool
        Star::can_transition(char c) const {
            return inner->can_transition(c);
        }

        void
        Star::reset() {
            match_count = 0;
            _valid = true;
            _captured = stringstream();
            xd = stringstream();
        }

        IPattern *
        Star::clone_pattern(bool withstate) const {
            Star *p = new Star(inner->clone_pattern(withstate));
            if(withstate) {
                p->match_count = match_count;
                p->_valid = _valid;
                p->_captured << _captured.str();
                p->xd << xd.str();
            }
            return p;
        }

        void
        Star::serialize_to( ostream &out ) const {
            ((Pattern*)inner)->serialize_to(out);
            out << "*";
        }

        string
        Star::rhizome_type() const {
            return "pattern::Star";
        }

        bool
        Star::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Pattern"||name=="Closure(Pattern)";
        }

        Thing *
        Star::invoke( Thing *context,string const &method, Thing *arg ) {
            (void)method;(void)arg; (void)context;
            throw runtime_error("Nothing to invoke.");
        }

        Thing *
        Star::captured_plain() {
            return new String(_captured.str());
        }

        Thing *
        Star::captured_transformed(){
            
            if( inner->accepted() ) {
                // check for remaining matched repetition.
                Thing *t = inner->captured_transformed();
                if( inner != NULL && ((Pattern*)inner)->rhizome_type()=="String" ) {
                    String *s = (String*)t;
                    xd << s->native_string();
                    delete t;
                    return new String(xd.str());
                } else {
                    delete t;
                    return new String(xd.str());
                }

            } if(accepted()) {
                return new String(xd.str());
            } else {
                stringstream err;
                err << "Attempted to capture part of a repetition of a pattern. \n";
                err << "This is most certainly an error. \nHere's some diagnostic info:\n";
                err << "This pattern: ";
                serialize_to(err);
                err << "\nCaptured plain: " << _captured.str() << "\n";
                err << "Captured transformed: " << xd.str() << "\n";
                throw runtime_error(err.str());
            }
        }
    }
}