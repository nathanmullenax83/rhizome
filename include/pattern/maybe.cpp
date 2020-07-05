#include "maybe.hpp"

namespace rhizome {
    namespace pattern {
        Maybe::Maybe( IPattern *inner ) : inner(inner) {

        }

        Maybe::~Maybe() {
            delete inner;
        }

        void Maybe::reset() {
            this->_captured = stringstream();
            this->_valid = true;
        }

        bool Maybe::can_transition( char c ) const {
            return inner->can_transition(c) && _captured.str().size()==0;
        }

        void Maybe::transition(char c) {
            if(!can_transition(c)) {
                stringstream err;
                err << "Cannot transition on '";
                err.put(c);
                err << "'. Pattern: ";
                serialize_to(err);
                throw runtime_error(err.str());
            }
            _captured.put(c);
            inner->transition(c);
        }

        bool Maybe::accepted() const {
            return (_valid && inner->accepted()) || (_valid && _captured.str()=="");
        }

        IPattern * Maybe::clone_pattern(bool withstate) const {
            Maybe *m = new Maybe(inner->clone_pattern(withstate));
            if( withstate ) {
                m->_captured << _captured.str();
                m->_valid = _valid;
            }
            return m;
        }

        void Maybe::serialize_to( std::ostream &out ) const {
            ((Pattern*)inner)->serialize_to(out);
            out << "?";
        }

        bool Maybe::has_interface( string const &name ) {
            return name==rhizome_type()||name=="pattern"||name=="Thing";
        }

        string Maybe::rhizome_type() const {
            return "pattern::Maybe";
        }

        Thing * Maybe::captured_plain() {
            return new String(_captured.str());
        }

        Thing * Maybe::captured_transformed() {
            assert(accepted());
            if( inner->accepted()) {
                return inner->captured_transformed();
            } else {
                return NULL;
            } 
        }

        Thing * Maybe::invoke(Thing *context, string const &method, Thing *arg ) {
            (void)method; (void)context; (void)arg;
            throw runtime_error("Not implemented.");
        }

        Maybe * maybe( IPattern *inner ) {
            return new Maybe(inner);
        }
    }
}