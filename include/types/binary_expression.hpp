#ifndef RHIZOME_TYPES_BINARY_EXPRESSION
#define RHIZOME_TYPES_BINARY_EXPRESSION

#include "core/thing.hpp"
#include "types/expression.hpp"


namespace rhizome {
    namespace types {
        /// This class represents a binary operation between two things:
        /// those things needn't be boolean!
        class BinaryExpression: public Expression {
        private:
            string op;
            Expression *left;
            Expression *right;
        public:
            BinaryExpression( string const &op, Expression *left, Expression *right );
            virtual ~BinaryExpression();

            // expression interface
            virtual Thing * evaluate( Thing *context ) const override;

            // thing interface
            virtual string rhizome_type() const override;
            virtual void serialize_to( size_t level, std::ostream &out ) const override;
            virtual bool has_interface( string const &method ) override;
            virtual Thing * clone() const override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;
        };
    }
}

#endif