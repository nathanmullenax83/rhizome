#ifndef RHIZOME_PARSE_LITERAL_HPP
#define RHIZOME_PARSE_LITERAL_HPP

#include <string>
#include "gramex.hpp"

using std::string;

namespace rhizome {
    namespace parse {
        class Literal: public Gramex {
        private:
            string value;
        public:
            Literal( string const &v );

            virtual bool can_match( ILexer *lexer, GrammarFn lookup ) const override;
            virtual void match( ILexer *lexer, GrammarFn lookup, stringstream &captured ) override;
            virtual bool accepts(GrammarFn lookup) const override;
            virtual Gramex * clone_gramex(bool withmatches) const override;

            // thing interface
            virtual void serialize_to( size_t level,std::ostream &out ) const override;
            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( Thing *context,string const &method, Thing *arg ) override;
            
        };

    }
}

#endif
