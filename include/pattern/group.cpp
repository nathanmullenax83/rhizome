#include "group.hpp"
#include "types/string.hpp"

using rhizome::types::String;

namespace rhizome {
    namespace pattern {
        Group::Group(IPattern *inner): inner(inner) {

        }

        Group::~Group() {
            delete inner;
        }

        void
        Group::reset() {
            inner->reset();
            _captured = stringstream();
            _valid = true;
        }
        
        bool
        Group::accepted() const {
            return _valid && inner->accepted();
        }

        void
        Group::transition(char c) {
            if( inner->can_transition(c) ) {
                inner->transition(c);
                _captured << c;
                return;
            } else {
                throw runtime_error("Group: cannot capture. Invalid transition.");
            }
        }

        bool
        Group::can_transition(char c) const {
            return inner->can_transition(c);
        }

        Thing *
        Group::captured_plain() {
            String *s = new String(_captured.str());
            reset();
            return s;
        }

        Thing *
        Group::captured_transformed() {
            return inner->captured_transformed();
        }

        IPattern * 
        Group::clone_pattern(bool withstate) const {
            Group *g = new Group(inner->clone_pattern(withstate));
            return g;
        }

        void
        Group::serialize_to( ostream &out ) const {
            out << "(";
            dynamic_cast<Thing*>(inner)->serialize_to(out);
            out << ")";
        }

        string
        Group::rhizome_type() const {
            return "pattern::Group";
        }

        bool
        Group::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Pattern"||"Closure"||"Thing";
        }

        Thing *
        Group::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)method;(void)arg;(void)context;
            throw runtime_error("Nothing to invoke.");
        }

    }
}