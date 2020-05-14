#include "or.hpp"

namespace rhizome {
    namespace pattern {

        bool
        Or::accepted() const {
            bool t(false);
            for(size_t i=0; i<clauses.size(); ++i) {
                if( clauses[i]->valid() && clauses[i]->accepted() ) {
                    return true;
                }
            }
            return t;
        }

        void
        Or::transition(char c) {
            for(size_t i=0; i<clauses.size(); ++i) {
                if( clauses[i]->valid() && clauses[i]->can_transition(c) ) {
                    clauses[i]->transition(c);
                } else {
                    clauses[i]->invalidate();
                }
            }
        }

        void
        Or::add_clause( IPattern *p ) {
            clauses.push_back(p);
        }

        bool
        Or::can_transition(char c) const {
            for(size_t i=0; i<clauses.size();++i) {
                if( clauses[i]->valid() && clauses[i]->can_transition(c)) {
                    return true;
                }
            }
            return false;
        }

        IPattern *
        Or::clone_pattern() const {
            vector<IPattern*> new_clauses;
            for(size_t i=0; i<clauses.size(); ++i) {
                new_clauses.push_back( clauses[i]->clone_pattern() );
            }
            Or *p = new Or();
            p->clauses = new_clauses;
            return p;
        }

        void
        Or::reset() {
            for(size_t i=0; i<clauses.size(); ++i) {
                clauses[i]->reset();
            }
            
            this->Pattern::reset();
        }

        Or::Or() {
            
        }

        Or::Or( IPattern *left, IPattern *right ) {
            clauses.push_back(left);
            clauses.push_back(right);
        }

        Or::~Or() {
            for(size_t i=0; i<clauses.size();++i) {
                delete clauses[i];
            }
        }

        void
        Or::serialize_to( ostream &out ) const {
            for(size_t i=0; i<clauses.size(); ++i) {
                ((Pattern*)clauses[i])->serialize_to(out);
                
                if( i+1 < clauses.size() ) {
                    out << "|";
                }
            }
        }

        string
        Or::rhizome_type() const {
            return "pattern::Or";
        }

        bool
        Or::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Pattern"||name=="Thing";
        }

        Thing *
        Or::invoke( string const &method, Thing *arg ) {
            (void)method;(void)arg;
            throw runtime_error("Nothing to invoke.");
        }
    }
}