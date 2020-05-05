#ifndef RHIZOME_PARSE_MATCH_TYPE_HPP
#define RHIZOME_PARSE_MATCH_TYPE_HPP

#include <string>
#include "gramex.hpp"

using std::string;

namespace rhizome {
    namespace parse {
        class MatchType: public Gramex {
        private:
            string name;
        public:
            MatchType( string const &name );

            virtual bool can_match( ILexer *lexer, GrammarFn lookup ) const override;
            virtual void match( ILexer *lexer, GrammarFn lookup ) override;
            virtual Gramex * clone_gramex() const override;

            virtual void serialize_to( std::ostream &out ) const override;
            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
        };
    }
}

#endif
