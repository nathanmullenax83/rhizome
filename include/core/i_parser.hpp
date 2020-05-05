#ifndef RHIZOME_CORE_I_PARSER_HPP
#define RHIZOME_CORE_I_PARSER_HPP

#include <iostream>
#include <string>
#include <deque>
#include <functional>
#include "pattern/pattern.hpp"
#include "core/i_gramex.hpp"
#include "core/thing.hpp"


using std::string;
using std::istream;
using std::deque;
using std::function;

using rhizome::core::Thing;

namespace rhizome {
    namespace core {
        

        class IParser {
        public:
            /* These methods are for deserialization:
               They are all helpers to use a system-configured parser that already excepts
               rhizome-specific tokens. */

            /// Match a literal token or throw
            virtual string match_literal( istream &in, string const &w) = 0; 

            /// Match an integer or throw
            virtual string match_integer( istream &in ) = 0;

            /// Match a double or throw
            virtual string match_float( istream &in ) = 0;

            /// Match a quoted string
            virtual string match_qstring( istream &in ) = 0;

            /// Match a specific pattern 
            virtual string match_pattern( istream &in, Pattern *p ) = 0;


            

            virtual Thing * parse_thing( string const &start_rule ) = 0;

            virtual void q_stream( istream &in ) = 0;

            // This used to be part of 'IGrammar' 
            virtual IGramex * lookup( string const &name ) const = 0;
        };
    }
}

#endif
