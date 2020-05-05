#include "maybe_closure.hpp"

namespace rhizome {
    namespace parse {
        MaybeClosure::MaybeClosure( Gramex *inner ): inner(inner) {

        }

        MaybeClosure::~MaybeClosure() {
            delete inner;
        }
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
        bool
        MaybeClosure::can_match( ILexer *lexer, GrammarFn lookup ) const {
            return true;
        }
#pragma GCC diagnostic pop

        void
        MaybeClosure::match( ILexer *lexer, GrammarFn lookup) {
            Gramex *copy = inner->clone_gramex();
            if( lexer->has_next_thing() && copy->can_match(lexer,lookup)) {
                copy->match(lexer,lookup);
                append_all(copy->clone_matched_tokens());
            }
            delete copy;
            
        }

        Gramex *
        MaybeClosure::clone_gramex() const {
            return new MaybeClosure( inner->clone_gramex());
        }

        void
        MaybeClosure::serialize_to( ostream &out ) const {
            out << "(";
            inner->serialize_to(out);
            out << ")?";
        }


        string
        MaybeClosure::rhizome_type() const {
            return "gramex::MaybeClosure";
        }

        bool
        MaybeClosure::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Gramex"||name=="Thing";
        }
    }
}