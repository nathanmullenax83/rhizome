#include "or.hpp"
#include "types/string.hpp"


using rhizome::types::String;

namespace rhizome {
    namespace pattern {
        void
        Or::dump(std::ostream &out) const {
            out << "\nDEBUG: pattern::Or " << (_valid?"Valid":"Not valid") << "\n";
            for( size_t i=0; i<clauses.size(); ++i) {
                out << "\t";
                ((Pattern*)clauses[i])->serialize_to(out);
                out << "\t";
                out << (clauses[i]->valid()?"Valid":"Not valid");
                out << "\t'";
                clauses[i]->captured_plain()->serialize_to(out);
                out << "'\n";
            }
        }

        bool
        Or::accepted() const {
            if( !_valid ) return false;
            bool t(false);
            for(size_t i=0; i<clauses.size(); ++i) {
                if( clauses[i]->accepted() ) {
                    return true;
                }
            }
            return t;
        }

        void
        Or::transition(char c) {
            bool pass = false;
            for(size_t i=0; i<clauses.size(); ++i) {
                if( clauses[i]->can_transition(c) ) {
                    clauses[i]->transition(c);
                    pass = true;
                } else {
                    clauses[i]->invalidate();
                }
            }
            if(!pass) {
                stringstream err;
                err << "No transition available for pattern ";
                serialize_to(err);
                err << "\n";
                err << "Captured so far: '" << _captured.str() << "'";
                throw runtime_error(err.str());
            }
            _captured.put(c);
        }

        void
        Or::add_clause( IPattern *p ) {
            clauses.push_back(p);
        }

        bool
        Or::can_transition(char c) const {
            for(size_t i=0; i<clauses.size();++i) {
                if( clauses[i]->can_transition(c)) {
                    return true;
                }
            }
            return false;
        }

        IPattern *
        Or::clone_pattern(bool withstate) const {
            vector<IPattern*> new_clauses;
            for(size_t i=0; i<clauses.size(); ++i) {
                new_clauses.push_back( clauses[i]->clone_pattern(withstate) );
            }
            Or *p = new Or();
            p->clauses = new_clauses;
            if( withstate) {
                p->_valid = _valid;
                p->_captured << _captured.str();
            }
            return p;
        }

        void
        Or::reset() {
            //std::cout << "Or reset. \n";
            _valid = true;
            _captured = stringstream();
            for(size_t i=0; i<clauses.size(); ++i) {
                clauses[i]->reset();   
            }
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

        Thing *
        Or::captured_plain() {
            // return capture of first accepted pattern
            return new String(_captured.str());
        }

        Thing *
        Or::captured_transformed() {
            if( accepted() ) {
                for(size_t i=0; i<clauses.size(); ++i) {
                    if( clauses[i]->accepted()) {
                        return clauses[i]->captured_transformed();
                    }
                }
                {
                    stringstream err;
                    err << "Couldn't find a matching clause: ";
                    serialize_to(err);
                    err << "\n";
                    err << "Plain capture so far: '";
                    err << _captured.str();
                    throw runtime_error(err.str());
                }
            } else {
                stringstream err;
                err << "Cannot capture transformed input, "
                    "as OR expression is not in an accept state.\n";
                err << "Captured so far: '" << _captured.str() << "'";
                dump(err);
                throw runtime_error(err.str());
            }
        }
    }
}