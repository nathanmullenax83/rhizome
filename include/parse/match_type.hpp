#ifndef RHIZOME_PARSE_MATCH_TYPE_HPP
#define RHIZOME_PARSE_MATCH_TYPE_HPP

#include <string>
#include "gramex.hpp"
#include "core/i_debuggable.hpp"

using std::string;
using rhizome::core::IDebuggable;

namespace rhizome {
    namespace parse {
        class MatchType: public IDebuggable, public Gramex {
        private:
            string name;
        public:
            MatchType( string const &name );

            virtual bool can_match( ILexer *lexer, GrammarFn lookup ) const override;
            virtual void match( ILexer *lexer, GrammarFn lookup, stringstream &captured ) override;
            virtual Gramex * clone_gramex(bool withmatches) const override;

            virtual void serialize_to( std::ostream &out ) const override;
            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( string const &method, Thing *arg ) override;

            virtual void dump( std::ostream &out ) const override;
            virtual bool accepts(GrammarFn lookup) const override;
        };
    }
}

#endif
