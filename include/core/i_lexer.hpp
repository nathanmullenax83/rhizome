#ifndef RHIZOME_CORE_I_LEXER
#define RHIZOME_CORE_I_LEXER
#include <deque>
#include <iostream>
#include <functional>
#include "thing.hpp"
#include "i_token.hpp"
#include "i_pattern.hpp"

using std::function;
using std::ostream;
using std::deque;
using rhizome::core::Thing;
using rhizome::core::IPattern;

namespace rhizome {
    namespace core {
        /// Interface for lexers.
        class ILexer {
        public:
            virtual ~ILexer();

            /// Define a token conversion: return NULL for ignore.
            // virtual void define_token_type( string const &name, IPattern *pattern, function< Thing*(Thing*) > ctor ) = 0;
            virtual void define_token_type( string const &name, IPattern *pattern ) = 0;

            /// Remove a pattern by name.
            virtual void undefine_token_type( string const &name ) = 0;

            /// Check if there is another token available
            virtual bool has_next_thing() const = 0;

            /// Extract the next token
            virtual Thing * next_thing( string &putback) = 0;

            /// Extract the next token only if it matches pattern name
            virtual Thing * next_thing( string const &pattern_name,string &putback ) = 0;
            
            /// Put a token back.
            //virtual void put_back( stringstream &s ) = 0;
            virtual void put_back( string const &s ) = 0;

            /// Look ahead without removing (0) is the next thing.
            /// This creates a copy using new, so don't forget to 
            /// delete!
            virtual deque<Thing *> peek_next_thing(size_t count, bool skipnulls) = 0;

            /// Look up a pattern by name (you own the pointer!)
            virtual IPattern * clone_pattern( string const &name ) const = 0;

            virtual void dump( std::ostream &out ) {
                out << "Debugging dump not implemented (ILexer)\n";
            };

        };
        
    }
}

#endif
