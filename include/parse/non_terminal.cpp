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
            return g->can_match(lexer,lookup);

        }

        void
        NonTerminal::match( ILexer *lexer, GrammarFn lookup ) {
            IGramex *g = ( lookup(name) );
            g->match( lexer, lookup );
            append_all( g->get_matched_tokens());
            delete g;
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