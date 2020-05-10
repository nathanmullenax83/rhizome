#include "digit.hpp"

namespace rhizome {
    namespace pattern {
        Digit::Digit(): state(0) {

        }

        Digit::~Digit() {

        }

        IPattern * 
        Digit::clone_pattern() const {
            Digit *clone = new Digit();
            clone->state = state;
            return clone;
        }

        bool
        Digit::accepted() const {
            return state==1;
        }

        bool
        Digit::can_transition(char c) const {
            return state==0 && isdigit(c);
        }

        void
        Digit::transition(char c) {
            if( can_transition(c) ) {
                ++state;
                return;
            }
            throw runtime_error("Digit pattern could not accept");
        }

        void
        Digit::reset() {
            state = 0;
            this->Pattern::reset();
        }

        void
        Digit::serialize_to_cclass_context( ostream &out ) const {
            out << ":digit:";
        }

        string
        Digit::rhizome_type() const {
            return "pattern::Digit";
        }

        bool
        Digit::has_interface( string const &name )  {
            return name==rhizome_type()||name=="Pattern"||name=="CClass"||name=="Thing";
        }

        void
        Digit::serialize_to( ostream &out ) const {
            out << "[";
            serialize_to_cclass_context(out);
            out << "]";
        }

        Thing *
        Digit::invoke( string const &method, Thing *arg ) {
            (void)method;(void)arg;
            throw runtime_error("Nothing to invoke.");
        }
    }
}