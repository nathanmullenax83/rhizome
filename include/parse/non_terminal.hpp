#ifndef RHIZOME_PARSE_NON_TERMINAL_HPP
#define RHIZOME_PARSE_NON_TERMINAL_HPP

#include <cstdlib>
#include <string>
#include "gramex.hpp"

using std::string;

namespace rhizome {
    namespace parse {
        class NonTerminal: public Gramex {
        private:
            string name;
        public:
            explicit NonTerminal( string const &name );
            string ID() const;

            virtual bool can_match( ILexer *lexer, GrammarFn lookup ) const override;
            virtual void match( ILexer *lexer, GrammarFn lookup ) override;
            virtual Gramex * clone_gramex() const override;

            virtual void serialize_to( std::ostream &out ) const override;
            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
            virtual bool accepts(GrammarFn lookup) const override;
            virtual Thing * invoke( string const &method, Thing *arg ) override;
        };
    }
}

#endif
