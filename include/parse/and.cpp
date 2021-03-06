#include "and.hpp"


#include "log.hpp"
#include <cassert>

namespace rhizome {
    namespace parse {
        namespace ands {
            static Dispatcher<And> dispatcher({
                {
                    "add clause",[]( Thing *context, And *that, Thing *arg ) {
                        (void)context;
                        assert( arg!=NULL && arg->has_interface("gramex"));
                        that->append( (Gramex*)arg );
                        return that;
                    }
                },
                {
                    "size", []( Thing *context, And *that, Thing *arg) {
                        (void)context;
                        assert(arg==NULL);
                        return new rhizome::types::Integer(that->size());
                    }
                }
            });
        }

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
            //      serialize_to(p);
            //      log.info(p.str());
            //  }
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
        And::serialize_to(size_t level, ostream &out ) const {
            out << "(";
            for(size_t i=0; i<clauses.size(); ++i) {
                clauses[i]->serialize_to(level,out);
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

        size_t 
        And::size() const {
            return clauses.size();
        }

        bool
        And::has_interface( string const &name) {
            return name==rhizome_type()||name=="gramex"||name=="Thing";
        }

        Thing * And::invoke( Thing *context, string const &method, Thing *arg ) {

            try {
                return ands::dispatcher.at(method)(context,this,arg);
            } catch( std::exception *e ) {
                stringstream err;
                err << "Attempted to invoked '" << method << "' on gramex::And but received an exception:\n";
                err << e->what();
                if( context != NULL ) {
                    err << "\nContext:\n";
                    context->serialize_to(1,err);
                }
                throw runtime_error(err.str());
            }
        } 
    }
}