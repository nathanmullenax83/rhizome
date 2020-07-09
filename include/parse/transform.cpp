#include "transform.hpp"

#include "log.hpp"

namespace rhizome {
    namespace parse {
        Transform::Transform( Gramex *inner, TransformFn transform ): inner(inner), transform(transform) {

        }

        bool Transform::can_match( ILexer *lexer, GrammarFn lookup ) const {
            return lexer->has_next_thing() && inner->can_match( lexer, lookup );
        }

        void Transform::match( ILexer *lexer, GrammarFn lookup, stringstream &captured ) {
            //static rhizome::log::Log log("xform_match");

            Gramex *copy = inner->clone_gramex(false);
            
            copy->match( lexer, lookup, captured );
            //log.info("Matched inner gramex.");
            Thing * made = transform( copy->clone_matched_tokens() );
            //log.info("Applied transform to copy of matched tokens.");
            copy->clear();
            //log.info("Cleared matched tokens from copy of gramex.");
            delete copy;
            //log.info("Deleted copy of gramex.");
            append_all( {made});

        }

        Gramex * Transform::clone_gramex(bool withmatches) const {
            Transform *t = new Transform( inner->clone_gramex(withmatches), transform );
            if( withmatches ) {
                t->append_all( clone_matched_tokens());
            }
            return t;
        }

        void Transform::serialize_to( size_t level, std::ostream &out ) const {
            (void)level;
            out << "F(";
            inner->serialize_to(0,out);
            out << ")";
        }

        bool Transform::has_interface( string const &name ) {
            return name==rhizome_type()||name=="gramex"||name=="Thing";
        }

        string Transform::rhizome_type() const {
            return "gramex::Transform";
        }

        bool Transform::accepts( GrammarFn lookup ) const {
            return inner->accepts(lookup);
        }

        Thing *
        Transform::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)method; (void)arg; (void)context;
            throw runtime_error("Invoke failed.");
        }
    }
}