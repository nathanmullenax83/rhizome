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
                    if( clauses[i]->can_match( lexer, lookup )) {
                        clauses[i]->match(lexer,lookup);
                        clear();
                        append_all( clauses[i]->get_matched_tokens());
                        return;
                    }
                }
                throw runtime_error("No match for this rule.");
            } catch (std::exception e) {
                stringstream ss;
                ss << "Received an exception matching OR: " << e.what() << "\n";
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