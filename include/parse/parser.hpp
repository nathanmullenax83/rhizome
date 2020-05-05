#ifndef RHIZOME_PARSE_PARSER_HPP
#define RHIZOME_PARSE_PARSER_HPP

#include <map>
#include <vector>
#include <tuple>
#include <sstream>

#include "types.hpp"
#include "pattern.hpp"
#include "lex.hpp"
#include "gramex.hpp"
#include "ruleset.hpp"
#include "literal.hpp"
#include "or.hpp"
#include "and.hpp"
#include "non_terminal.hpp"
#include "match_type.hpp"
#include "plus_closure.hpp"
#include "star_closure.hpp"

#include "core/i_parser.hpp"

using std::pair;
using std::map;
using std::vector;
using std::string;
using std::stringstream;


namespace types = rhizome::types;
namespace pat = rhizome::pattern;
namespace lex = rhizome::lex;

using lex::Lexer;
using rhizome::core::IParser;
using rhizome::core::IGramex;

namespace rhizome {
    namespace parse {
        class Parser: public Thing, public IParser {
        private:
            Ruleset rules;
            Lexer lexer;
        public:
            

            Parser();
            void rule( string const &w, Gramex *expr, ParseFn parser);

            // token-level matchers
            virtual string match_literal( istream &in, string const &token ) override;
            virtual string match_float( istream &in ) override;
            virtual string match_integer( istream &in ) override;
            virtual string match_qstring( istream &in ) override;
            virtual string match_pattern( istream &in, Pattern *p ) override;

            virtual IGramex * lookup( string const &name ) const override;
            // virtual Thing * parse_thing( istream &in, string const &start_rule,
            //     IGrammar *grammar, ParseFn f ) override;
            
            virtual Thing * parse_thing( string const &start_rule ) override;

            virtual void q_stream( istream &in ) override;

            virtual string rhizome_type() const override;
            virtual void serialize_to( std::ostream &out ) const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * clone() const override;

        };

        Gramex * lit(string const &w);
        Gramex * seq(Gramex *a, Gramex *b);
        Gramex * seq(Gramex *a, Gramex *b, Gramex *c);
        Gramex * seq(Gramex *a, Gramex *b, Gramex *c, Gramex *d);
        

        Gramex * options( std::vector<Gramex *> cs );

        Gramex * non_term(string const &name);
        Gramex * match_type( string const &tname);

        // match '(' inner ')'
        Gramex * parens( Gramex *inner );

        // match a, b, c
        Gramex * comma_list( std::vector<Gramex*> elems, string sep="," );

        /// Match one or more of a sentence.
        Gramex * plus( Gramex * inner );

        /// Match any number of a sentence
        Gramex * star( Gramex * inner );
        
        /// Match zero or one of a sentence.
        Gramex * maybe( Gramex * inner );

        
    }
}

#endif
