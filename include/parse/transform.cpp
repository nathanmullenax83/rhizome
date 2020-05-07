#include "transform.hpp"

namespace rhizome {
    namespace parse {
        Transform::Transform( Gramex *inner, TransformFn transform ): inner(inner), transform(transform) {

        }

        bool Transform::can_match( ILexer *lexer, GrammarFn lookup ) const {
            return inner->can_match( lexer, lookup );
        }

        void Transform::match( ILexer *lexer, GrammarFn lookup ) {
            Gramex *copy = inner->clone_gramex();
            copy->match( lexer, lookup );
            Thing * made = transform( copy->clone_matched_tokens() );
            copy->clear();
            delete copy;
            append_all( {made});
        }

        Gramex * Transform::clone_gramex() const {
            Transform *t = new Transform( inner->clone_gramex(), transform );
            return t;
        }

        void Transform::serialize_to( std::ostream &out ) const {
            inner->serialize_to(out);
        }

        bool Transform::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Gramex"||name=="Thing";
        }

        string Transform::rhizome_type() const {
            return "gramex::Transform";
        }
    }
}