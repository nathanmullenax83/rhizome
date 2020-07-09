#include <cassert>
#include <stdexcept>
#include "binary_expression.hpp"
using rhizome::core::Dispatcher;
using rhizome::core::indent;
using std::runtime_error;

namespace rhizome {
    namespace types {

        namespace bexp {
            static Dispatcher<BinaryExpression> dispatcher({
                {
                    "evaluate",[] (Thing *context, BinaryExpression *that, Thing *arg) {
                        assert(arg==NULL);
                        return that->evaluate(context);
                    }
                }
            });
        }

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

        string 
        BinaryExpression::rhizome_type() const {
            return "BinExp";
        }
        
        void
        BinaryExpression::serialize_to( size_t level, std::ostream &out ) const {
            out << "\n" << indent(level) << rhizome_type() << " {\n";
            out << indent(level+1) << "op: \"" << op << "\"\n";
            
            out << indent(level+1) << "left: ";
            left->serialize_to(level+2,out);
            out << "\n";

            out << indent(level+1) << "right: ";
            right->serialize_to(level+2,out);
            out << "\n";

            out << indent(level) << "}\n";
        }
        
        bool
        BinaryExpression::has_interface( string const &name ) {
            return name=="Thing"||name=="expression"||name==rhizome_type();
        }

        Thing *
        BinaryExpression::clone() const {
            BinaryExpression *copy = new BinaryExpression(
                op,
                (Expression*)left->clone(),
                (Expression*)right->clone()
            );
            return copy;
        }

        Thing *
        BinaryExpression::invoke( Thing *context, string const &method, Thing *arg ) {
            try {
                Thing *r = bexp::dispatcher.at(method)(context,this,arg);
                return r;
            } catch( std::exception *e ) {
                if( bexp::dispatcher.count(method)==0) {
                    throw runtime_error(rhizome::core::invoke_method_not_found(method,this,context));
                } else {
                    throw runtime_error(rhizome::core::invoke_error(method,arg,this,context,e));
                }
            }
        }
    }
}