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
            virtual void match( ILexer *lexer, GrammarFn lookup ) override;

            virtual Gramex * clone_gramex() const;

            virtual void serialize_to(ostream &out) const override;
            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
            virtual bool accepts(GrammarFn lookup) const override;
        };
    }
}

#endif
