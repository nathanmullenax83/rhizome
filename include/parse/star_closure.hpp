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
            virtual void match( ILexer *lexer, GrammarFn lookup, stringstream &captured ) override;

            virtual Gramex * clone_gramex(bool withmatches) const override;

            virtual void serialize_to(size_t level, ostream &out) const override;
            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;
            virtual bool accepts( GrammarFn lookup ) const override;
        };
    }
}

#endif
