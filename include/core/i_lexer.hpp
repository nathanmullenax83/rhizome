#ifndef RHIZOME_CORE_I_LEXER
#define RHIZOME_CORE_I_LEXER
#include <iostream>
#include <functional>
#include "thing.hpp"
#include "i_token.hpp"
#include "i_pattern.hpp"

using std::function;
using std::ostream;
using rhizome::core::Thing;
using rhizome::core::IPattern;

namespace rhizome {
    namespace core {
        /// Interface for lexers.
        class ILexer {
        public:
            /// Define a token conversion: return NULL for ignore.
            virtual void define_token_type( string const &name, IPattern *pattern, function< Thing*(IToken*) > ctor ) = 0;
            virtual void define_token_type( string const &name, IPattern *pattern, function< Thing*(void) > ctor ) = 0;

            /// Remove a pattern by name.
            virtual void undefine_token_type( string const &name ) = 0;

            /// Check if there is another token available
            virtual bool has_next_thing() const = 0;

            /// Extract the next token
            virtual Thing * next_thing() = 0;
            
            /// Put a token back.
            virtual void put_back_thing( Thing *t ) = 0;

            /// Look ahead without removing (0) is the next thing.
            /// This creates a copy using new, so don't forget to 
            /// delete!
            virtual Thing * peek_next_thing(size_t i) = 0;

            virtual void dump( std::ostream &out ) {
                out << "Debugging dump not implemented (ILexer)\n";
            };

        };
        
    }
}

#endif
