#ifndef RHIZOME_PARSE_PLUS_CLOSURE_HPP
#define RHIZOME_PARSE_PLUS_CLOSURE_HPP

#include "gramex.hpp"

namespace rhizome {
    namespace parse {
        class PlusClosure: public Gramex {
        private:
            Gramex *inner;
        public:
            PlusClosure( Gramex *inner );
            virtual ~PlusClosure();

            virtual bool can_match( ILexer *lexer, GrammarFn lookup ) const override;
            virtual void match( ILexer *lexer, GrammarFn lookup, stringstream &captured) override;

            virtual Gramex * clone_gramex(bool withmatches) const;

            virtual void serialize_to(size_t level,ostream &out) const override;
            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;
            virtual bool accepts(GrammarFn lookup) const override;
        };
    }
}

#endif
