#ifndef RHIZOME_PARSE_MATCH_RULE_HPP
#define RHIZOME_PARSE_MATCH_RULE_HPP

#include "gramex.hpp"

namespace rhizome {
    namespace parse {
        /// Match a lexer rule. This is different than matching a type, and in
        /// some cases more expensive, though not particularly so. 
        class MatchRule: public Gramex {
        private:
            string name;
        public:
            MatchRule( string const & rulename );

            virtual bool can_match( ILexer *lexer, GrammarFn lookup ) const override;
            virtual void match( ILexer *lexer, GrammarFn lookup, stringstream &captured ) override;
            virtual Gramex * clone_gramex(bool withmatches) const override;

            virtual void serialize_to( std::ostream &out ) const override;
            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;

            virtual bool accepts(GrammarFn lookup) const override;
        };
    }
}

#endif