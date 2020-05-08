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
        NonTerminal::match( ILexer *lexer, GrammarFn lookup ) {
            std::cout << "-- non-terminal: " << name << " ";
            IGramex *g =  lookup(name);
            assert(g!=NULL && lexer !=NULL);
            ((Gramex*)g)->serialize_to(std::cout);
            std::cout << "\n";
            g->match( lexer, lookup );
            append_all( g->clone_matched_tokens());
            delete g;
            std::cout << "-- non-terminal.";
        }

        Gramex *
        NonTerminal::clone_gramex() const {
            NonTerminal *nt = new NonTerminal(name);
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
            return name==rhizome_type()||name=="Gramex"||name=="Thing";
        }
    }
}