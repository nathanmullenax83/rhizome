#ifndef RHIZOME_PARSE_OR_HPP
#define RHIZOME_PARSE_OR_HPP

#include <vector>
#include "gramex.hpp"
#include "core/i_debuggable.hpp"

using std::vector;
using rhizome::core::IDebuggable;

namespace rhizome {
    namespace parse {
        class Or: public IDebuggable, public Gramex {
        private:
            vector<Gramex *> clauses;
        public:
            Or();
            virtual ~Or();

            /// Define a new clause for an or expression
            void add_clause( Gramex *option );

            virtual bool can_match( ILexer *lexer, GrammarFn lookup ) const override;
            virtual void match( ILexer *lexer, GrammarFn lookup, stringstream &captured ) override;
            virtual Gramex * clone_gramex(bool withmatches) const override;

            virtual void serialize_to( size_t level, ostream &out ) const override;
            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;
            virtual bool accepts( GrammarFn lookup ) const override;

            // debug dump:
            virtual void dump(std::ostream &out) const override;
        };
    }
}

#endif

