#ifndef RHIZOME_TYPES_REFERENCE_EXPRESSION
#define RHIZOME_TYPES_REFERENCE_EXPRESSION

#include "types/expression.hpp"
#include "types/type_constraint.hpp"
#include "types/string.hpp"

using rhizome::types::Expression;
using rhizome::types::TypeConstraint;

namespace rhizome {
    namespace types {
        
        /// You cannot lookup a variable without specifying a type constraint.
        /// Rest assured, there will be a 'any' type.
        class ReferenceExpression : public Expression {
        private:
            string name;
            TypeConstraint *reftype;

        public:
            ReferenceExpression( string const &name, TypeConstraint *tc );
            virtual ~ReferenceExpression();

            virtual string Name() const;

            /// Does this reference refer to a variable that exists and satisfies that type constraint?
            virtual bool valid( Thing *context ) const;

            // thing interface
            virtual string rhizome_type() const override;
            virtual void serialize_to(std::ostream &out) const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * clone() const override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;

            // expression interface
            virtual Thing * evaluate( Thing *context ) const override; // 'deref'
        };
    }
}

#endif