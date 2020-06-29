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
            {
                stringstream gx; 
                gx << "Copied inner gramex: ";
                copy->serialize_to(gx);
                //log.info(gx.str());
            }
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

        void Transform::serialize_to( std::ostream &out ) const {
            out << "F(";
            inner->serialize_to(out);
            out << ")";
        }

        bool Transform::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Gramex"||name=="Thing";
        }

        string Transform::rhizome_type() const {
            return "gramex::Transform";
        }

        bool Transform::accepts( GrammarFn lookup ) const {
            return inner->accepts(lookup);
        }

        Thing *
        Transform::invoke( string const &method, Thing *arg ) {
            (void)method; (void)arg;
            throw runtime_error("Invoke failed.");
        }
    }
}