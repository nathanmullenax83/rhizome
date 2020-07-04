#include "star_closure.hpp"

#include "log.hpp"

namespace rhizome {
    namespace parse {
        StarClosure::StarClosure( Gramex *inner ): inner(inner) {

        }

        StarClosure::~StarClosure() {
            delete inner;
        }

        bool
        StarClosure::accepts( GrammarFn lookup ) const {
            (void)lookup;
            return true;
        }

        void
        StarClosure::match( ILexer *lexer, GrammarFn lookup, stringstream &captured ) {
            //static rhizome::log::Log log("cfg_STAR");
            
            //log.info("Match called.");

            Gramex *copy = inner->clone_gramex(false);

            //log.info("Copied gramex.");

            while( copy->can_match(lexer,lookup)) {
                
                //log.info("Match available.");
                copy->match(lexer,lookup,captured);
                //log.info("Match complete.");
                append_all(copy->clone_matched_tokens());
                //log.info("Match extracted.");
                copy->clear();
                //log.info("Copy of gramex cleared.");
            }

            //log.info("Match complete. Deleting copy of gramex.");
            delete copy;
        }

        bool
        StarClosure::can_match( ILexer *lexer, GrammarFn lookup ) const  {
            Gramex *copy = inner->clone_gramex(false);
            bool cm = (!lexer->has_next_thing()) || copy->can_match(lexer,lookup);
            delete copy;
            return  cm;
        }

        Gramex * 
        StarClosure::clone_gramex(bool withmatches) const {
            StarClosure *s = new StarClosure(inner->clone_gramex(withmatches));
            if(withmatches) {
                s->append_all(clone_matched_tokens());
            }
            return s;
        }

        void
        StarClosure::serialize_to( ostream &out ) const {
            out << "(";
            inner->serialize_to(out);
            out << ")*";
        }

        string
        StarClosure::rhizome_type() const {
            return "gramex::StarClosure";
        }

        bool
        StarClosure::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Gramex"||name=="Thing";
        }

        Thing *
        StarClosure::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)method; (void)arg; (void)context;
            throw runtime_error("Invoke failed.");
        }
    }
}