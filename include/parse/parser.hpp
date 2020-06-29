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
#include "transform.hpp"
#include "match_rule.hpp"
#include "maybe_closure.hpp"

#include "core/i_parser.hpp"
#include "core/i_debuggable.hpp"

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
using rhizome::core::IDebuggable;

namespace rhizome {
    namespace parse {
        class Parser: public Thing, public IParser, public IDebuggable {
        private:
            Ruleset rules;
            Lexer *lexer;

        public:
            /// Create a parser with default system lexer.
            Parser();
            /// Create a parser with a specific lexer (Parser owns pointer).
            Parser(Lexer *lexer);

            ~Parser();

            void clear();

            void rule( string const &w, Gramex *expr);

            virtual IGramex * lookup( string const &name ) const override;
            
            virtual Thing * parse_thing( string const &start_rule ) override;

            virtual Thing * parse_thing( string const &start_rule, string const &thing ) override;

            virtual void q_stream( istream &in ) override;

            virtual string rhizome_type() const override;
            
            virtual void serialize_to( std::ostream &out ) const override;

            virtual bool has_interface( string const &name ) override;

            virtual Thing * invoke( string const &method, Thing *arg ) override;

            virtual Thing * clone() const override;

            virtual void dump(std::ostream &out) const override;

            virtual ILexer * get_lexer() override;

        };

        Gramex * lit(string const &w);
        Gramex * seq(Gramex *a, Gramex *b);
        Gramex * seq(Gramex *a, Gramex *b, Gramex *c);
        Gramex * seq(Gramex *a, Gramex *b, Gramex *c, Gramex *d);
        Gramex * seq(vector<Gramex*> es);
        

        Gramex * options( std::vector<Gramex *> cs );

        Gramex * non_term(string const &name);
        Gramex * match_type( string const &tname);
        Gramex * match_lexer_rule( string const &rule_name );

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

        /// Apply a function to a match sequence
        Gramex * apply( Gramex * inner, TransformFn f );

        
    }
}

#endif
