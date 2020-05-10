#ifndef RHIZOME_PARSE_TRANSFORM
#define RHIZOME_PARSE_TRANSFORM

#include <functional>
#include "gramex.hpp"

using rhizome::parse::Gramex;

using std::function;

namespace rhizome {
    namespace parse {
        typedef function< Thing *( deque<Thing*> ) > TransformFn;

        class Transform: public Gramex {
        private:
            Gramex *inner;
            TransformFn transform;

        public:
            Transform( Gramex *inner, TransformFn transform );

            virtual bool can_match( ILexer *lexer, GrammarFn lookup ) const override;
            virtual void match( ILexer *lexer, GrammarFn lookup ) override;

            virtual Gramex * clone_gramex() const override;

            virtual void serialize_to(ostream &out) const override;
            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( string const &method, Thing *arg ) override;
            virtual bool accepts( GrammarFn lookup ) const override;
        };
    }
}

#endif
