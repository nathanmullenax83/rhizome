#ifndef RHIZOME_CORE_I_GRAMEX_HPP
#define RHIZOME_CORE_I_GRAMEX_HPP

#include <deque>
#include <functional>
#include "lex.hpp"
#include "i_lexer.hpp"

using std::deque;
using std::function;
using rhizome::lex::Token;

using rhizome::core::ILexer;


namespace rhizome {
    namespace core {
        class IGramex;
        
        typedef function< IGramex * ( string const & ) > GrammarFn;

        class IGramex {
        public:
            virtual ~IGramex() {}
            virtual bool can_match( ILexer *lexer, GrammarFn lookup ) const = 0;
            virtual void match( ILexer *lexer, GrammarFn lookup ) = 0;
            virtual deque<Thing *> get_matched_tokens() = 0;
            virtual deque<Thing *> clone_matched_tokens() const = 0;
        };
    }
}

#endif
