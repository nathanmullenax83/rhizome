#ifndef RHIZOME_LEXER_HPP
#define RHIZOME_LEXER_HPP

#include <iostream>
#include <string>
#include <map>
#include <regex>
#include <vector>
#include <deque>
#include <cctype>
#include <queue>
#include <functional>
#include <tuple>
#include <stack>

#include "pattern.hpp"
#include "token.hpp"
#include "stream_queue.hpp"
#include "token_queue.hpp"
#include "core/i_debuggable.hpp"
#include "core/i_lexer.hpp"
#include "types.hpp"


using std::string;
using std::map;
using std::vector;
using std::deque;
using std::function;
using std::regex;
using std::queue;
using std::istream;
using std::pair;
using std::stack;

using rhizome::pattern::Group;
using rhizome::core::IDebuggable;
using rhizome::core::ILexer;
using rhizome::core::IPattern;
using rhizome::types::String;

namespace rhizome {
    namespace lex {
        typedef function< Thing *( IToken * ) > TokenConstructor;


        /// Converts a character stream into a token stream.
        class Lexer: public ILexer, public IDebuggable, public Thing {
        private:
            struct PatternRecord {
                Group *pattern;
                TokenConstructor ctor;
            };

            struct LexerState {
                // type registry
                // name -> type_id
                map<string, PatternRecord> patterns;
                
                // input streams
                StreamQueue streams;
                // output token stream
                TokenQueue tokens;
            };

            stack< LexerState > states;
        public:
            void push_state();
            void pop_state();
            virtual void dump( ostream &out ) const override;
        private:
            // to summarize: tokens are extracted from streams according to patterns.

            // Helpers
            // reset all patterns.
            void reset_patterns();
        public:
            /// Create a lexer streaming lexer.
            Lexer(  );
            virtual ~Lexer();

            /// process this stream after whatever else is queued
            void q( istream &str );
        private:
            void define( string const &name, rhizome::pattern::Group *g);

            /// Bulk define a bunch of keywords of the same type ID.            
            
            void define( string const &name, string const &token_literal );

        public:
            void define( string const &name, vector<string> const &keywords );
            bool has_next() const;
            Thing * next(bool skipcheck=false);
            //void put_back(Token t);
            void put_back_thing(Thing *t);

            virtual Thing * peek_next_thing( size_t index ) override;


            bool direct_has_next( istream &in );
            Thing * direct_next( istream &in );

            // lexer interface
            virtual void define_token_type( string const &name, IPattern *p, function< Thing*(IToken*) > ctor ) override;
            virtual void define_token_type( string const &name, string const &literal );
            virtual void define_token_type( string const &name, IPattern *p, function< Thing*(void) > ctor) override;
            virtual void undefine_token_type( string const &name );
            virtual bool has_next_thing() const override;
            virtual Thing * next_thing() override;

            // thing interface
            virtual void serialize_to( std::ostream &out ) const override;
            
            virtual string rhizome_type() const override;
            virtual Thing * clone() const override;
            virtual bool has_interface( string const &name ) override;


        };

        void demo();
    }
}

#endif