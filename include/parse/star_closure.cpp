#include "star_closure.hpp"

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
        StarClosure::match( ILexer *lexer, GrammarFn lookup ) {
#ifdef INSTRUMENTED
            std::cout << "-- Star: ";
            inner->serialize_to(std::cout);
            std::cout << "\n";
#endif
            Gramex *copy = inner->clone_gramex();
            while( lexer->has_next_thing() && copy->can_match(lexer,lookup)) {
                
                copy->clear();
                copy->match(lexer,lookup);
                append_all(copy->clone_matched_tokens());
            }
            delete copy;
        }

        bool
        StarClosure::can_match( ILexer *lexer, GrammarFn lookup ) const  {
            Gramex *copy = inner->clone_gramex();
            bool cm = (!lexer->has_next_thing()) || copy->can_match(lexer,lookup);
            delete copy;
            return  cm;
        }

        Gramex * 
        StarClosure::clone_gramex() const {
            return new StarClosure(inner->clone_gramex());
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
        StarClosure::invoke( string const &method, Thing *arg ) {
            (void)method; (void)arg;
            throw runtime_error("Invoke failed.");
        }
    }
}