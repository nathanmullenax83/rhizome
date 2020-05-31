#include "cat.hpp"
#include "types/string.hpp"

using rhizome::types::String;

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
            if( !_valid) return false;
            
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
                    _captured.put(c);
                    
                    return;
                } else if( parts[state]->accepted() && (state+1 < parts.size())) {
                    ++state;
                    parts[state]->transition(c);
                    _captured.put(c);
                    return;
                } else {
                    throw runtime_error("Cat: no transition available.");
                }
            }
        }

        bool
        Cat::can_transition(char c) const {
            if( state < parts.size() ) {
                if( parts[state]->can_transition(c)) {
                    return true;
                } else if( parts[state]->accepted() ) {
                    if( state+1 < parts.size() ) {
                        return parts[state+1]->can_transition(c);
                    }
                } 
            }
            return false;
        }

        void
        Cat::reset() {
            state = 0;
            for(size_t i=0; i<parts.size(); ++i) {
                ((Pattern*)parts[i])->reset();
            }
            _valid = true;
            _captured = stringstream();
        }

        IPattern *
        Cat::clone_pattern(bool withstate) const {
            Cat *p = new Cat();
            vector<IPattern *> new_parts;
            for(size_t i=0; i<parts.size(); ++i) {
                new_parts.push_back( parts[i]->clone_pattern(withstate) );
            }
            p->parts = new_parts;
            if( withstate ) {
                p->state = state;
                p->_captured << _captured.str();
                p->_valid = _valid;
            }
            return p;
        }

        void
        Cat::serialize_to( ostream &out ) const {
            for(size_t i=0; i<parts.size(); ++i) {
                ((Pattern*)parts[i])->serialize_to(out);
                if( i+1<parts.size() ) {
                    out << "⁀";
                }
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

        Thing *
        Cat::invoke( string const &method, Thing *arg ) {
            (void)method;(void)arg;
            throw runtime_error("Nothing to invoke.");
        }

        Thing *
        Cat::captured_transformed () {
            assert( accepted() );
            // oh boy:
            stringstream capd;
            for(size_t i=0; i<parts.size(); ++i) {
                
                Thing *s = parts[i]->captured_transformed();
                if( s!=NULL && s->rhizome_type()=="String") {
                    s->serialize_to(capd);
                }
                
            }
            return new String(capd.str());
        }

        Thing *
        Cat::captured_plain() {
            return new String(_captured.str());
        }

        Cat * cat( vector<IPattern *> const &parts ) {
            Cat *c = new Cat();
            for(size_t i=0; i<parts.size(); ++i) {
                c->append((Pattern*)parts.at(i));
            }
            return c;
        }
    }
}