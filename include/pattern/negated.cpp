#include "negated.hpp"
#include "types/string.hpp"

using rhizome::types::String;

namespace rhizome {
    namespace pattern {
        Negated::Negated( CClass *inner ): inner(inner), n_accepted(0) {

        }

        Negated::~Negated() {
            delete inner;
        }

        bool 
        Negated::accepted() const {
            return _valid && n_accepted==1 && !inner->accepted();
        }

        bool
        Negated::can_transition( char c ) const {
            return n_accepted==0 && !inner->can_transition(c);
        }

        void
        Negated::transition(char c) {
            if( can_transition(c) ) {
                n_accepted++;
                _captured.put(c);
                return;
            } else {
                stringstream err;
                err << "Could not transition on " << /* printable */ c << ".";
                throw runtime_error(err.str());
            }
        }

        void
        Negated::reset() {
            n_accepted = 0;
            inner->reset();
            _valid = true;
            _captured = stringstream();
        }

        Thing *
        Negated::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)method;(void)arg; (void)context;
            throw runtime_error("Nothing to invoke.");
        }

        Pattern *
        Negated::clone_pattern(bool withstate) const {
            Negated *n = new Negated( (CClass*)inner->clone_pattern(withstate) );
            if( withstate ){
                n->_valid = _valid;
                n->_captured<< _captured.str();
                n->n_accepted = n_accepted;
            }
            return n;
        }

        void
        Negated::serialize_to_cclass_context( std::ostream &out ) const {
            out << "~";
            inner->serialize_to(0,out);
        }

        void
        Negated::serialize_to(size_t level, std::ostream &out) const {
            (void)level;
            out << "[";
            serialize_to_cclass_context(out);
            out << "]";
        }

        bool
        Negated::has_interface( string const &name ) {
            return name==rhizome_type()||name=="CClass"||name=="Thing";
        }

        string
        Negated::rhizome_type() const {
            return "cclass::Negated";
        }
        Thing *
        Negated::captured_plain() {
            return new String(_captured.str());
        }

        Thing *
        Negated::captured_transformed() {
            return captured_plain();
        }
        
    }
}