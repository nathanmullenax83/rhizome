#include "group.hpp"

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
            this->Pattern::reset();
        }
        
        bool
        Group::accepted() const {
            return inner->accepted();
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

        string 
        Group::captured() const {
            return _captured.str();
        }

        IPattern * 
        Group::clone_pattern() const {
            Group *g = new Group(inner->clone_pattern());
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

    }
}