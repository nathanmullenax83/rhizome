#include "nongreedy.hpp"

#include "types/string.hpp"

using rhizome::core::indent;
using rhizome::core::Dispatcher;

namespace rhizome {
    namespace pattern {
        namespace nongreedy {
            static Dispatcher<NonGreedy> dispatcher({

            });
        }

        NonGreedy::NonGreedy( Pattern *inner ) : inner(inner) {
            
        }

        NonGreedy::~NonGreedy() {
            delete inner;
        }

        bool
        NonGreedy::accepted() const {
            return _valid && inner->accepted();
        }

        bool
        NonGreedy::can_transition(char c) const {
            if( accepted() ) return false;
            return inner->can_transition(c);
        }

        void
        NonGreedy::transition(char c) {
            _captured.put(c);
            return inner->transition(c);
        }

        void
        NonGreedy::reset() {
            inner->reset();
            _valid = true;
            _captured = stringstream();
        }

        Thing *
        NonGreedy::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)method;(void)arg; (void)context;
            throw runtime_error("Nothing to invoke.");
        }

        
        
        Thing * 
        NonGreedy::captured_transformed() {
            return inner->captured_transformed();
        }

        Thing *
        NonGreedy::captured_plain() {
            return new rhizome::types::String(this->_captured.str());
        }

        Pattern *
        NonGreedy::clone_pattern(bool withstate) const {
            NonGreedy *ng = new NonGreedy((Pattern*)inner->clone_pattern(withstate));
            if( withstate) {
                ng->_valid = _valid;
                ng->_captured << _captured.str();
            }
            return ng;
        }
        
        string 
        NonGreedy::rhizome_type() const {
            return "pattern::Negated";
        }

        bool
        NonGreedy::has_interface( string const &name ) {
            return name=="Thing"||name=="pattern"||name==rhizome_type();
        }

        Thing *
        NonGreedy::clone() const {
            return clone_pattern(true);
        }

        void
        NonGreedy::serialize_to( size_t level, std::ostream &out ) const {
            out << "(";
            inner->serialize_to(level,out);
            out << ")?";
        }


    }
}