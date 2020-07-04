#ifndef RHIZOME_TYPES_OPERATOR
#define RHIZOME_TYPES_OPERATOR

#include <string>
#include <functional>
#include <vector>
#include "core/thing.hpp"
#include "tuple.hpp"
#include <cassert>

using rhizome::core::Thing;
using rhizome::types::Tuple;
using std::wstring;
using std::function;
using std::vector;

namespace rhizome {
    namespace types {
        enum OperatorType {
            PREFIX, INFIX, POSTFIX, NONFIX
        };

        enum OperatorAssociativity {
            LEFT_TO_RIGHT,
            RIGHT_TO_LEFT
        };

        typedef function<Thing*(void)> UnitFunction;
        typedef function<Thing*(Thing*) > UnaryFunction;
        typedef function<Thing*(Thing*,Thing*) > BinaryFunction;
        typedef function<Thing*(Tuple*) > NAryFunction;

        

        class Operator : public Thing {
        private:
            // it's a vector to support tern-, quatern-, septern-, etceteraries.
            vector<wstring> op;
            OperatorType t;
            OperatorAssociativity associativity;
            size_t arity_from;
            size_t arity_to;

            UnitFunction    unit_f;
            UnaryFunction   unary_f;
            BinaryFunction  binary_f;
            NAryFunction    nary_f;

            Operator();
        public:
            /// Not really an operator so much as a special function taking no arguments
            Operator( wstring op, UnitFunction apply );

            /// Unary operator constructor (prefix or suffix)
            Operator( wstring op, UnaryFunction apply, OperatorType t );

            /// binary infix operator constructor
            Operator( wstring op, BinaryFunction apply, OperatorAssociativity assoc );

            /// n-ary pre or post fix e.g., (PLUS 1 2 34 5 3)
            /// design note: apply maybe a 'Thing' which happens to be evaluable.
            Operator( wstring op, NAryFunction apply,  OperatorType t);

            /// Sigh. Ternary, etc.
            /// This is a weird compromize for now. The argument is passed as a tuple.
            /// There will be an automatic runtime check to make sure than the size of 
            /// the tuple matches 'arity'. 
            /// @param{t} can be any of the operator type, as one could, in theory make an operator like:
            /// * 8 -> 1 : 2  is a prefix operator of arity 3
            /// * 8 -> 1 : 2 . is the same operator with a dummy terminator (still prefix)
            /// booleanExpr ? v1 : v2 is the ordinary ternary (infix arity 2)
            Operator( vector<wstring> ops, size_t arity, NAryFunction apply, OperatorType t);

            virtual void serialize_to( std::ostream &out ) const override;
            virtual string rhizome_type() const override;
            virtual Thing * clone() const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *argument ) override;
        };
    }
}

#endif