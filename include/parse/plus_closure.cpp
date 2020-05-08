#include "plus_closure.hpp"

namespace rhizome {
    namespace parse {
        PlusClosure::PlusClosure( Gramex *inner ): inner(inner) {

        }

        PlusClosure::~PlusClosure() {
            delete inner;
        }

        bool 
        PlusClosure::can_match( ILexer *lexer, GrammarFn lookup ) const {
            return lexer->has_next_thing() && inner->can_match(lexer,lookup);
        }

        void
        PlusClosure::match( ILexer *lexer, GrammarFn lookup ) {
            // required to match at least once
            Gramex *copy = inner->clone_gramex();
            copy->clear();
        
            copy->match( lexer, lookup );
            append_all( copy->clone_matched_tokens() );
            copy->clear();
            
            while( lexer->has_next_thing() && copy->can_match(lexer,lookup)) {
                copy->match( lexer, lookup );
                append_all(copy->clone_matched_tokens());
                copy->clear();
            }
            delete copy;
        }

        bool
        PlusClosure::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Gramex"||name=="Thing";
        }

        Gramex *
        PlusClosure::clone_gramex() const {
            return new PlusClosure( inner->clone_gramex() );
        }

        void
        PlusClosure::serialize_to( ostream &out ) const {
            out << "(";
            inner->serialize_to(out);
            out << ")+";
        }

        string
        PlusClosure::rhizome_type() const {
            return "gramex::PlusClosure";
        }

        bool
        PlusClosure::accepts( GrammarFn lookup ) const {
            return inner->accepts(lookup);
        }
    }
}