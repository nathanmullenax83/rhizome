#include "binary_expression.hpp"

namespace rhizome {
    namespace types {

        BinaryExpression::BinaryExpression( string const &op, Expression *left, Expression *right) 
        :op(op), left(left), right(right) {
            // implementation note: left expression must define operation /op/
        }

        BinaryExpression::~BinaryExpression() {
            delete left;
            delete right;
        }

        Thing * 
        BinaryExpression::evaluate( Thing *context ) const {
            // how can I simply presume that left can be evaluated before right?
            // Only by assuming that left and right have no side effects, and 
            // therefore no bearing on one another.
            Thing *l_eval = left->evaluate(context);
            Thing *r_eval = right->evaluate(context);
            // compute the result. Note: vtable for left type determines the operation.
            Thing *result = l_eval->invoke(context,op,r_eval);
            // get rid of intermediate values.
            delete l_eval; 
            delete r_eval;
            // the final result is your pointer.
            return result;
        }
        
        

    }
}