#ifndef RHIZOME_PARSE_GRAMEX_HPP
#define RHIZOME_PARSE_GRAMEX_HPP

#include <deque>
#include <stdexcept>
#include "lex.hpp"
#include "core/i_lexer.hpp"
#include "core/i_gramex.hpp"
#include "core/thing.hpp"

using std::deque;
using std::runtime_error;
using rhizome::lex::Lexer;
using rhizome::lex::Token;
using rhizome::core::IGramex;
using rhizome::core::ILexer;
using rhizome::core::Thing;
using rhizome::core::GrammarFn;

namespace rhizome {
    namespace parse {
        /// Grammatical Expression: represents anything that appears
        /// on the right hand side of a BNF rule.
        class Gramex: public IGramex, public Thing {
        protected:
            void append_all( deque<Thing*> ts );
        private:
            deque< Thing* > matched_tokens;
        public:
            virtual void clear();
        public:
            

            virtual ~Gramex();
            /// Check if the next however-many tokens can match this expression 
            /// without extracting them. Note, we need to be able to expand non-
            /// terminals, so an interface to the grammar table is passed in.
            virtual bool can_match( ILexer *lexer, GrammarFn lookup) const = 0;

            /// Match and extract tokens or throw an error.
            virtual void match( ILexer *lexer, GrammarFn lookup ) = 0;

            virtual Gramex * clone_gramex() const = 0;
            virtual Thing * clone() const;

            //virtual deque<Thing*> get_matched_tokens() override;
            virtual deque<Thing*> clone_matched_tokens() const override;

            virtual size_t match_count() const;
        };
    }
}

#endif
