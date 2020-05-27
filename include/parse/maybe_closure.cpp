#include "maybe_closure.hpp"

namespace rhizome {
    namespace parse {
        MaybeClosure::MaybeClosure( Gramex *inner ): inner(inner) {

        }

        MaybeClosure::~MaybeClosure() {
            delete inner;
        }

        bool MaybeClosure::accepts(GrammarFn lookup) const {
            (void)lookup;
            return true;
        }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
        bool
        MaybeClosure::can_match( ILexer *lexer, GrammarFn lookup ) const {
            return true;
        }
#pragma GCC diagnostic pop

        void
        MaybeClosure::match( ILexer *lexer, GrammarFn lookup, stringstream &captured) {
            Gramex *copy = inner->clone_gramex(false);
#ifdef INSTRUMENTED
            std::cout << "-- maybe [";
            copy->serialize_to(std::cout);
            std::cout << "\n";
#endif
            if( lexer->has_next_thing() && copy->can_match(lexer,lookup)) {
                copy->match(lexer,lookup,captured);
                append_all(copy->clone_matched_tokens());
            }
            delete copy;
#ifdef INSTRUMENTED
            std::cout << "-- /maybe\n";
#endif
        }

        Gramex *
        MaybeClosure::clone_gramex(bool withmatches) const {
            MaybeClosure *maybe = new MaybeClosure( inner->clone_gramex(withmatches));
            if( withmatches ) {
                maybe->append_all( clone_matched_tokens());
            }
            return maybe;
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

        Thing *
        MaybeClosure::invoke( string const &method, Thing *arg ) {
            (void)method; (void)arg;
            throw runtime_error("Not implemented. (maybe closure)");
        }
    }
}