#include "and.hpp"

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
        And::clone_gramex() const {
            And *n = new And();
            for(size_t i=0; i<clauses.size();++i) {
                n->clauses.push_back( clauses[i]->clone_gramex() );
            }
            return n;
        }

        void
        And::append( Gramex *g ) {
            clauses.push_back(g);
        }

        void
        And::match( ILexer *lexer, GrammarFn lookup ) {
            for( size_t i=0; i<clauses.size(); ++i ) {
                // copy clause
                Gramex *c_i = clauses[i]->clone_gramex();
                c_i->clear();
                c_i->match( lexer, lookup );
                append_all( c_i->clone_matched_tokens() );
                delete c_i;
            }
        }

        bool
        And::can_match( ILexer *lexer, GrammarFn lookup ) const {
            if( !lexer->has_next_thing() ) return false;
            deque<Thing*> matched;

            for( size_t i=0; i<clauses.size(); ++i) {
                Gramex *copy = clauses[i]->clone_gramex();
                copy->clear();
                if( copy->can_match(lexer,lookup)) {
                    copy->match(lexer,lookup);
                    deque<Thing*> ts = copy->clone_matched_tokens();
                    for(size_t j=0; j<ts.size(); ++j) {
                        matched.push_back( ts[j]->clone() );
                    }
                } else {
                    for(int j=matched.size()-1; j>=0; --j) {
                        lexer->put_back_thing( matched[j]);
                    }
                    return false;
                }
                delete copy;
            }
            // Can match all clauses of AND -- putting back tokens.
            for(int j=matched.size()-1; j>=0; --j) {
                lexer->put_back_thing( matched[j]);
            }
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
    }
}