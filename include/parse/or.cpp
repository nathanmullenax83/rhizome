#include "or.hpp"

namespace rhizome {
    namespace parse {
        Or::Or() {

        }

        Or::~Or() {
            for(size_t i=0; i<clauses.size();++i) {
                delete clauses[i];
            }
        }

        bool
        Or::accepts( GrammarFn lookup ) const {
            bool t_accept(false); // at least one clause trivially accepts.
            for(size_t i=0; i<clauses.size(); ++i) {
                t_accept = t_accept || clauses[i]->accepts(lookup);
            }
            return t_accept;
        }

        void Or::dump( std::ostream &out ) const {
            try {
                out << "DEBUG DUMP (gramex::Or)\n";
                out << "=======================\n";
                out << "Clauses\n";
                for(size_t i=0; i<clauses.size();++i) {
                    out << "\t" << i << ": ";
                    clauses[i]->serialize_to(out);
                    out << "\n";
                }
                out << "Matched tokens\n";
                auto tokens = clone_matched_tokens();
                for(size_t i=0; i<tokens.size(); ++i) {
                    out << "\t";
                    tokens[i]->serialize_to(out);
                    out << "\n";
                }
            } catch ( std::exception *e ) {
                out << "\nGot an error generating debug dump!\n";
            }
        }

        Gramex *
        Or::clone_gramex(bool withmatches) const {
            Or *n = new Or();
            for(size_t i=0; i<clauses.size(); ++i) {
                n->clauses.push_back( clauses[i]->clone_gramex(withmatches) );
            }
            if( withmatches ) {
                n->append_all( clone_matched_tokens() );
            }
            return n;
        }

        void
        Or::add_clause( Gramex *clause ) {
            clauses.push_back(clause);
        }

        void
        Or::match( ILexer *lexer, GrammarFn lookup, stringstream &captured ) {
#ifdef INSTRUMENTED
            std::cout << "-- Or\n";
#endif
            try {
                for(size_t i=0; i<clauses.size(); ++i) {
                    Gramex *copy = clauses[i]->clone_gramex(false);
                    if( copy->can_match( lexer, lookup ) || copy->accepts(lookup)) {
#ifdef INSTRUMENTED
                        std::cout << "Matched or clause:";
                        copy->serialize_to(std::cout);
                        std::cout << "\n";
#endif
                        copy->match(lexer,lookup,captured);
                        append_all( copy->clone_matched_tokens());
                        delete copy;
                        return;
                    } else {
                        delete copy;
                    }
                }
                //dump(std::cout);
                //throw runtime_error("No match for this rule.");
            } catch (std::exception *e) {
                stringstream ss;
                ss << "Received an exception matching OR: " << e->what() << "\n";
                dump(ss);
                throw runtime_error(ss.str());
            }
        }

        bool
        Or::can_match( ILexer *lexer, GrammarFn lookup ) const {
            if( !lexer->has_next_thing() ) return false;
            for(size_t i=0; i<clauses.size(); ++i) {
                if( clauses[i]->can_match(lexer, lookup)) {
                    return true;
                }
            }
            return false;
        }

        void
        Or::serialize_to( ostream &out ) const {
            for(size_t i=0; i<clauses.size(); ++i) {
                clauses[i]->serialize_to(out);
                if( i<clauses.size()-1) {
                    out << "|";
                }
            }
        }

        string
        Or::rhizome_type() const {
            return "gramex::Or";
        }

        bool
        Or::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Gramex"||name=="Thing";
        }

        Thing *
        Or::invoke( string const &method, Thing *arg ) {
            (void)method;(void)arg;
            throw runtime_error("Or/invoke/whatever not implemented.");
        }
    }
}