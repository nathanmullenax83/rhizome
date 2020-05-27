#include "and.hpp"


#include "log.hpp"

namespace rhizome {
    namespace parse {
        And::And() {

        }

        And::~And() {
            for(size_t i=0; i<clauses.size(); ++i) {
                delete clauses[i];
            }
        }

        Gramex *
        And::clone_gramex(bool withmatches) const {
            And *n = new And();
            for(size_t i=0; i<clauses.size();++i) {
                n->clauses.push_back( clauses[i]->clone_gramex(withmatches) );
            }
            if( withmatches ) {
                n->append_all( clone_matched_tokens() );
            }
            return n;
        }

        bool
        And::accepts(GrammarFn lookup) const {
            // all clauses may accept trivially.
            bool t_accept(true);
            for(size_t i=0; i<clauses.size();++i) {
                t_accept = t_accept && clauses[i]->accepts(lookup);
            }
            return clauses.size()==0 || t_accept;
        }

        void
        And::append( Gramex *g ) {
            clauses.push_back(g);
        }

        void
        And::match( ILexer *lexer, GrammarFn lookup, stringstream &captured ) {
            // static rhizome::log::Log log("seq_match");
            // {
            //     stringstream p;
            //     serialize_to(p);
            //     log.info(p.str());
            // }
#ifdef INSTRUMENTED
            std::cout << "-- Sequence ";
            serialize_to(std::cout);
            std::cout << "\n";
#endif
            for( size_t i=0; i<clauses.size(); ++i ) {
                // copy clause
                Gramex *c_i = clauses[i]->clone_gramex(false);
                c_i->match( lexer, lookup, captured );
                //log.info("Captured: ");
                //log.info(captured.str());
                append_all( c_i->clone_matched_tokens() );
                delete c_i;
            }
#ifdef INSTRUMENTED
            std::cout << "-- /Sequence\n";
#endif
        }

        bool
        And::can_match( ILexer *lexer, GrammarFn lookup ) const {
            //static rhizome::log::Log log("and_canmatch");
            if( !lexer->has_next_thing() ) return false;
            stringstream captured;

            deque<Thing*> matched;
            auto delete_matched = [&matched] {
                for(size_t i=0; i<matched.size();++i) {
                    delete matched[i]; matched[i] = NULL;
                }
                matched.clear();
                return;
            };

            for( size_t i=0; i<clauses.size(); ++i) {
                Gramex *copy = clauses[i]->clone_gramex(false);
                if( copy->can_match(lexer,lookup) || copy->accepts(lookup)) {
                    copy->match(lexer,lookup,captured);
                    deque<Thing*> ts = copy->clone_matched_tokens();
                    for(size_t j=0; j<ts.size(); ++j) {
                        matched.push_back( ts[j] );
                    }
                } else {
                    delete_matched();
                    //std::cout << "And pattern did not match.\n";
                    //std::cout << "Putting back: '" << captured.str() << "\n";
                    lexer->put_back( captured.str() );
                    
                    return false;
                }
                delete copy;
            }
            delete_matched();
            //log.info("Putting back:");
            //log.info(captured.str());
            lexer->put_back( captured.str());
            return true;
        }

        void 
        And::serialize_to( ostream &out ) const {
            out << "(";
            for(size_t i=0; i<clauses.size(); ++i) {
                clauses[i]->serialize_to(out);
                if( i<(clauses.size()-1) ) {
                    out << " ";
                }
            }
            out << ")";
        }

        string
        And::rhizome_type() const {
            return "gramex::And";
        }

        bool
        And::has_interface( string const &name) {
            return name==rhizome_type()||name=="Gramex"||name=="Thing";
        }

        Thing * And::invoke( string const &method, Thing *arg ) {
            (void)method; (void)arg;
            throw runtime_error("Don't do that!");
        } 
    }
}