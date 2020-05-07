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
        Or::clone_gramex() const {
            Or *n = new Or();
            for(size_t i=0; i<clauses.size(); ++i) {
                n->clauses.push_back( clauses[i]->clone_gramex() );
            }
            return n;
        }

        void
        Or::add_clause( Gramex *clause ) {
            clauses.push_back(clause);
        }

        void
        Or::match( ILexer *lexer, GrammarFn lookup ) {
            try {
                for(size_t i=0; i<clauses.size(); ++i) {
                    Gramex *copy = clauses[i]->clone_gramex();
                    copy->clear();
                    if( copy->can_match( lexer, lookup )) {
                        std::cout << "Matched or clause:";
                        copy->serialize_to(std::cout);
                        std::cout << "\n";
                        copy->match(lexer,lookup);
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
    }
}