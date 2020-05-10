#include "star.hpp"

namespace rhizome {
    namespace pattern {
        Star::Star( IPattern *inner ): inner(inner) {

        }

        Star::~Star() {
            delete inner;
        }

        bool
        Star::accepted() const {
            return true;
        }

        void
        Star::transition(char c) {
            if( inner->can_transition(c) ) {
                inner->transition(c);
                if( inner->accepted() ) {
                    inner->reset();
                }
                return;
            } else if( inner->accepted() ) {
                match_count++;
                inner->reset();
                inner->transition(c);
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
            this->Pattern::reset();
        }

        IPattern *
        Star::clone_pattern() const {
            Star *p = new Star(inner->clone_pattern());
            p->match_count = match_count;
            return p;
        }

        void
        Star::serialize_to( ostream &out ) const {
            out << "(?:";
            ((Thing*)inner)->serialize_to(out);
            out << ")*";
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
        Star::invoke( string const &method, Thing *arg ) {
            (void)method;(void)arg;
            throw runtime_error("Nothing to invoke.");
        }
    }
}