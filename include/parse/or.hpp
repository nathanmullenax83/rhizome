#ifndef RHIZOME_PARSE_OR_HPP
#define RHIZOME_PARSE_OR_HPP

#include <vector>
#include "gramex.hpp"

using std::vector;

namespace rhizome {
    namespace parse {
        class Or: public Gramex {
        private:
            vector<Gramex *> clauses;
        public:
            Or();
            virtual ~Or();

            /// Define a new clause for an or expression
            void add_clause( Gramex *option );

            virtual bool can_match( ILexer *lexer, GrammarFn lookup ) const override;
            virtual void match( ILexer *lexer, GrammarFn lookup ) override;
            virtual Gramex * clone_gramex() const override;

            virtual void serialize_to( ostream &out ) const override;
            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
        };
    }
}

#endif

