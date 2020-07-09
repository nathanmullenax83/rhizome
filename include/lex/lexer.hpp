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
       // typedef function< Thing *( IToken * ) > TokenConstructor;
        class LexerState {
        public:
            LexerState();
            // type registry
            // name -> type_id
            map<string, IPattern *> patterns;
             
            // input streams
            StreamQueue streams;
                
            // output token stream
            //TokenQueue tokens;
        };

        /// Converts a character stream into a token stream.
        class Lexer: public ILexer, public IDebuggable, public Thing {
        private:
            size_t row;
            size_t col;

            

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
            void define( string const &name, IPattern *g);

            /// Bulk define a bunch of keywords of the same type ID.            
            
            void define( string const &name, string const &token_literal );
            //virtual void eat_null_productions();
        public:
            /// Clear all streams and queued tokens.
            void clear();
            
            virtual void define( string const &name, vector<string> const &keywords );
            virtual bool has_next() const;

            virtual wchar_t peek_next_character();

            virtual Thing * next(string &putback);
            //void put_back(Token t);
            // virtual void put_back(stringstream &s) override;
            virtual void put_back( string const &s) override;

            
            virtual deque<Thing *> peek_next_thing( size_t count, bool skipnulls ) override;


            //bool direct_has_next( istream &in );
            //Thing * direct_next( istream &in );

            // lexer interface
            // virtual void define_token_type( string const &name, IPattern *p, function< Thing*(Thing*) > ctor ) override;
            virtual void define_token_type( string const &name, string const &literal );
            virtual void define_token_type( string const &name, IPattern *p ) override;

            // Shortcut for a generic rule to ignore whitespace
            virtual void define_ignore_whitespace();

            
            

            virtual void undefine_token_type( string const &name );
            virtual bool has_next_thing() const override;
            virtual bool has_next_thing( string const & ) override;
            virtual Thing * next_thing( string &putback ) override;
            virtual Thing * next_thing( string const &pattern_name, string &putback ) override;
            virtual IPattern * clone_pattern( string const &name ) const override;

            // thing interface
            virtual void serialize_to( size_t level, std::ostream &out ) const override;
            
            virtual string rhizome_type() const override;
            virtual Thing * clone() const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;


        };

        void demo();
    }
}

#endif