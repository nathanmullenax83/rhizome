#ifndef RHIZOME_PARSE_AND_HPP
#define RHIZOME_PARSE_AND_HPP

#include <vector>
#include "gramex.hpp"

using std::vector;

namespace rhizome {
    namespace parse {
        class And: public Gramex {
        private:
            vector< Gramex * > clauses;
        public:
            And();
            virtual ~And();

            void append( Gramex *g );
            size_t size() const;

            virtual bool can_match( ILexer *lexer, GrammarFn lookup ) const override;
            virtual void match( ILexer *lexer, GrammarFn lookup, stringstream &captured ) override;
            virtual Gramex * clone_gramex(bool withmatches) const override;

            virtual void serialize_to( ostream &out ) const override;
            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;
            virtual bool accepts(GrammarFn lookup) const override;
        };
    }
}

#endif
