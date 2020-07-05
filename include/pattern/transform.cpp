#include "transform.hpp"
#include "group.hpp"
#include "types/string.hpp"

using rhizome::types::String;

namespace rhizome {
    namespace pattern {
        Transform::Transform( IPattern *inner, TokenConstructor transform): transform(transform) {
            this->inner = new Group(inner);
        }

        Transform::~Transform() {
            delete inner;
        }



        void
        Transform::reset() {
            inner->reset();
            _valid = true;
            _captured = stringstream();
        }

        bool
        Transform::can_transition(char c) const {
            return inner->can_transition(c);
        }

        void
        Transform::transition(char c) {
            if( inner->can_transition(c)) {
                inner->transition(c);
                _captured.put(c);
                return;
            } else {
                throw runtime_error("Whitespace: invalid state transition");
            }
        }

        bool 
        Transform::accepted() const {
            return _valid && inner->accepted();
        }

        IPattern *
        Transform::clone_pattern(bool withstate) const {
            Transform *ts = new Transform(inner->clone_pattern(withstate),transform);
            if( withstate) {
                ts->_valid = _valid;
                ts->_captured << _captured.str();
            }
            return ts;
        }

        

        void 
        Transform::serialize_to( ostream &out ) const {
            out << "λ❨";
            ((Pattern*)inner)->serialize_to(out);
            out << "❩";
        }

        string
        Transform::rhizome_type() const {
            return "pattern::Transform";
        }

        bool
        Transform::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Pattern"||name=="Thing";
        }

        Thing *
        Transform::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)context;
            if( method=="clone" && arg==NULL ) return clone();
            throw runtime_error("Invalid invocation.");
        }

        Thing *
        Transform::captured_plain() {
            return new String(_captured.str());
        }

        Thing *
        Transform::captured_transformed() {
            return transform( inner->captured_transformed() );
        }

        bool
        Transform::verify(std::ostream &out) {
            // a transform can produce anything.
            // or nothing at all, so there isn't 
            // much we can do to test it from the inside.
            bool check = true;
            out << "Transform";
            return check;
        }
    }
}