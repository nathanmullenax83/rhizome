#include "plus.hpp"
#include "types/string.hpp"
#include "n_times.hpp"

using rhizome::pattern::NTimes;
using rhizome::types::String;

namespace rhizome {
    namespace pattern {
        Plus::Plus( IPattern *inner ): inner(inner), n_accepted(0) {

        }

        void
        Plus::reset() {
            n_accepted=0;
            _valid = true;
            _captured = stringstream();
            xd = stringstream();
            inner->reset();
        }

        bool
        Plus::can_transition(char c) const {
            if( inner->can_transition(c)) {
                return true;
            } else {
                IPattern *copy = inner->clone_pattern(false);
                bool p = copy->can_transition(c);
                delete copy;
                return p;
            }
        }

        void
        Plus::transition(char c) {
            if( !inner->can_transition(c) ) {
                // no transitions available
                if( inner->accepted()) {
                    String *s = (String*)inner->captured_transformed();
                    if( s!=NULL && s->rhizome_type()=="String" ) {
                        xd << s->native_string();
                        delete s;
                    }
                    inner->reset();
                    ++n_accepted;
                } else {
                    // inner cannot transition before or after reset: error
                    stringstream err;
                    err << "Plus: inner pattern cannot transition on '";
                    err.put(c);
                    err << "'\n";
                    ((Pattern*)inner)->serialize_to(err);
                    throw runtime_error(err.str());
                }
                inner->transition(c);
                _captured.put(c);
            } else {
                inner->transition(c);
                _captured.put(c);
            } 
        }

        bool
        Plus::accepted() const {
            return _valid && (inner->accepted() || n_accepted>0);
        }

        IPattern *
        Plus::clone_pattern(bool withstate) const {
            Plus *p = new Plus(inner->clone_pattern(withstate));
            if( withstate ) {
                p->_valid = _valid;
                p->n_accepted = n_accepted;
                p->xd << xd.str();
                p->_captured << _captured.str();
            }
            return p;
        }

        Thing *
        Plus::captured_transformed() {
            // there may be captured characters to extract:
            if( inner->accepted() ) {
                String *s = (String*)inner->captured_transformed();
                if( s!=NULL ) {
                    stringstream __captured;
                    __captured << xd.str() << s->native_string();
                    delete s;
                    return new String(__captured.str());
                }
                
            } 
            return new String(xd.str());
            
        }

        Thing *
        Plus::captured_plain() {
            return new String(_captured.str());
        }

        void
        Plus::serialize_to( ostream &out ) const {
            ((Pattern*)inner)->serialize_to(out);
            out << "+";
        }

        bool
        Plus::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Pattern"||name=="Thing";
        }

        string
        Plus::rhizome_type() const {
            return "pattern::Plus";
        }

        Thing *
        Plus::invoke( string const &method, Thing *arg ) {
            (void)method;(void)arg;
            throw runtime_error("Nothing to invoke.");
        }

        Plus * plus( IPattern *inner ) {
            return new Plus(inner);
        }
    }
}