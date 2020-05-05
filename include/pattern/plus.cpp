#include "plus.hpp"

namespace rhizome {
    namespace pattern {
        Plus::Plus( IPattern *inner ): inner(inner), n_accepted(0) {

        }

        void
        Plus::reset() {
            n_accepted=0;
            this->Pattern::reset();
        }

        bool
        Plus::can_transition(char c) const {
            if( inner->can_transition(c)) {
                return true;
            } else {
                IPattern *copy = inner->clone_pattern();
                copy->reset();
                bool p = copy->can_transition(c);
                delete copy;
                return p;
            }
        }

        void
        Plus::transition(char c) {
            if( inner->can_transition(c) ) {
                inner->transition(c);
            } 
            if( inner->accepted() ) {
                ++n_accepted;
                inner->reset();
                inner->transition(c);
            } else {
                throw runtime_error("Invalid transition.");
            }
        }

        bool
        Plus::accepted() const {
            return n_accepted>0;
        }

        IPattern *
        Plus::clone_pattern() const {
            Plus *p = new Plus(inner->clone_pattern());
            p->n_accepted = n_accepted;
            return p;
        }

        void
        Plus::serialize_to( ostream &out ) const {
            out << "(?:";
            ((Thing*)inner)->serialize_to(out);
            out << ")+";
        }

        bool
        Plus::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Pattern"||name=="Thing";
        }

        string
        Plus::rhizome_type() const {
            return "pattern::Plus";
        }
    }
}