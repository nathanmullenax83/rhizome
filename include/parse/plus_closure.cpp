#include "plus_closure.hpp"

#include "log.hpp"

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
        PlusClosure::match( ILexer *lexer, GrammarFn lookup, stringstream &captured ) {
            //static rhizome::log::Log log("plus_match");
            // required to match at least once

            Gramex *copy = inner->clone_gramex(false);
            //log.info("Created copy of inner pattern.");


            copy->match( lexer, lookup, captured );
            //log.info("Matched first repetition.");
            append_all( copy->clone_matched_tokens() );
            //log.info("Appended tokens associated with first repetition.");
            copy->clear();
            //log.info("Captured tokens (putback buffer)");
            //log.info(captured.str());
            while( lexer->has_next_thing() && inner->can_match(lexer,lookup)) {
                copy->match( lexer, lookup,captured );
                //log.info("Matched another repetition.");
                append_all(copy->clone_matched_tokens());
                copy->clear();
            }
            delete copy;
        }

        bool
        PlusClosure::has_interface( string const &name ) {
            return name==rhizome_type()||name=="gramex"||name=="Thing";
        }

        Gramex *
        PlusClosure::clone_gramex(bool withmatches) const {
            PlusClosure *p = new PlusClosure( inner->clone_gramex(withmatches) );
            if(withmatches) {
                p->append_all( clone_matched_tokens());
            }
            return p;
        }

        void
        PlusClosure::serialize_to( size_t level, ostream &out ) const {
            out << "(";
            inner->serialize_to(level, out);
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

        Thing *
        PlusClosure::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)method; (void)arg; (void)context;
            throw runtime_error("Invoke failed.");
        }
    }
}