#ifndef RHIZOME_PARSE_STAR_CLOSURE
#define RHIZOME_PARSE_STAR_CLOSURE

#include "gramex.hpp"

namespace rhizome {
    namespace parse {
        class StarClosure: public Gramex {
        private:
            Gramex *inner;
        public:
            StarClosure( Gramex *inner );
            ~StarClosure();

            virtual bool can_match( ILexer *lexer, GrammarFn lookup ) const override;
            virtual void match( ILexer *lexer, GrammarFn lookup ) override;

            virtual Gramex * clone_gramex() const override;

            virtual void serialize_to(ostream &out) const override;
            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
            virtual bool accepts( GrammarFn lookup ) const override;
        };
    }
}

#endif
