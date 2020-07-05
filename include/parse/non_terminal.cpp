#include "non_terminal.hpp"

namespace rhizome {
    namespace parse {
        NonTerminal::NonTerminal(string const &name): name(name) {

        }

        string
        NonTerminal::ID() const {
            return name;
        }

        bool
        NonTerminal::can_match( ILexer *lexer, GrammarFn lookup ) const {
            
            if( !lexer->has_next_thing() ) return false;
            IGramex *g =( lookup( name ) );
            bool m = g->can_match(lexer,lookup);
            
            return m;
            

        }

        bool
        NonTerminal::accepts(GrammarFn lookup) const {
            return lookup(name)->accepts(lookup);
        }

        void
        NonTerminal::match( ILexer *lexer, GrammarFn lookup, stringstream &captured ) {
#ifdef INSTRUMENTED
            std::cout << "-- non-terminal: '" << name << "' =  ";
#endif
            IGramex *g =  lookup(name);
#ifdef INSTRUMENTED
            ((Gramex*)g)->serialize_to(std::cout);
            std::cout << "\n";
#endif
            assert( g!=NULL && lexer !=NULL );
            // ((Gramex*)g)->serialize_to(std::cout);
            // std::cout << "\n";
            g->match( lexer, lookup,captured );
            append_all( g->clone_matched_tokens());
            delete g;
#ifdef INSTRUMENTED
            std::cout << "-- non-terminal.";
#endif
        }

        Gramex *
        NonTerminal::clone_gramex(bool withmatches) const {
            NonTerminal *nt = new NonTerminal(name);
            if( withmatches ) {
                nt->append_all( clone_matched_tokens());
            }
            return nt;
        }

        void
        NonTerminal::serialize_to( std::ostream &out ) const {
            out << name;
        }

        string
        NonTerminal::rhizome_type() const {
            return "gramex::NonTerminal";
        }

        bool
        NonTerminal::has_interface( string const &name ) {
            return name==rhizome_type()||name=="gramex"||name=="Thing";
        }

        Thing *
        NonTerminal::invoke( Thing *context, string const &method, Thing *arg ) {
            (void) method; (void)arg; (void)context;
            throw runtime_error("Nope.");
        }
    }
}