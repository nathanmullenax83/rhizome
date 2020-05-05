#include "cat.hpp"

namespace rhizome {
    namespace pattern {



        Cat::Cat(): state(0) {

        }

        Cat::Cat( IPattern *a, IPattern *b ): state(0) {
            parts.push_back(a);
            parts.push_back(b);
        }

        Cat::~Cat() {
            for(size_t i=0; i<parts.size(); ++i) {
                delete parts[i];
            }
        }

        void
        Cat::append( Pattern *p ) {
            parts.push_back(p);
        }

        bool 
        Cat::accepted() const {
            bool all(true);
            for(size_t i=0; i<parts.size(); ++i) {
                all = parts[i]->accepted() && all;
            }
            return all;
        }

        void
        Cat::transition(char c) {
            if( state >= parts.size() ) {
                throw runtime_error("Cat: Cannot transition because there are no more clauses.");
            } else {
                if( parts[state]->can_transition(c) ) {
                    parts[state]->transition(c);
                    return;
                } else if( parts[state]->accepted() ) {
                    ++state;
                    parts[state]->transition(c);
                    return;
                } else {
                    return;
                }
            }
        }

        bool
        Cat::can_transition(char c) const {
            if( state >= parts.size() ) return false;
            if( parts[state]->can_transition(c) ) return true;
            
            if( state+1 < parts.size() ) {
                return parts[state]->accepted() && parts[state+1]->can_transition(c);
            }
            return false;
        }

        void
        Cat::reset() {
            state = 0;
            for(size_t i=0; i<parts.size(); ++i) {
                parts[i]->reset();
            }
            this->Pattern::reset();
        }

        IPattern *
        Cat::clone_pattern() const {
            Cat *p = new Cat();
            vector<IPattern *> new_parts;
            for(size_t i=0; i<parts.size(); ++i) {
                new_parts.push_back( parts[i]->clone_pattern() );
            }
            p->parts = new_parts;
            p->state = state;
            return p;
        }

        void
        Cat::serialize_to( ostream &out ) const {
            for(size_t i=0; i<parts.size(); ++i) {
                ((Thing*)parts[i])->serialize_to(out);
            }
        }

        string 
        Cat::rhizome_type() const {
            return "pattern::Cat";
        }

        bool
        Cat::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Pattern"||name=="Thing";
        }
    }
}