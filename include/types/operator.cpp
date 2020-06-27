#include "operator.hpp"

#include <cwctype>
#include <string>
#include <codecvt>
#include <locale>

namespace rhizome {
    namespace types {
        Thing * unit_dummy() {
            throw runtime_error(" is not a unit operator.");
        }

        Thing * unary_dummy(Thing *a) {
            (void)a;
            throw runtime_error(" is not a unary operator.");
        }

        Thing * binary_dummy(Thing* a, Thing *b) {
            (void)a; (void)b;
            throw runtime_error(" is not a binary operator.");
        }

        Thing * nary_dummy( Tuple *t ) {
            (void)t;
            throw runtime_error(" is not an n-ary operator.");
        }
        // this is private--exclusively for cloning.
        Operator::Operator() {

        }

        Operator::Operator( wstring op, UnitFunction apply ) 
        : op({op}), unit_f(apply), unary_f(unary_dummy), binary_f(binary_dummy), nary_f(nary_dummy)
        {
            t = NONFIX;
            arity_from = arity_to = 0;
            
        }

        // unary pre- or post- fix. 
        Operator::Operator( wstring op, UnaryFunction apply, OperatorType t ) 
        : op({op}), unit_f(unit_dummy), unary_f(apply), binary_f(binary_dummy), nary_f(nary_dummy)
        {
            // consider ++p and ++++p
            assert( t!=INFIX ); // as that just doesn't make any sense.
            this->t = t;
            // if it's a prefix operator, then it should be right to left.
            // if it's postfix, then it has to be left to right
            associativity = (t==POSTFIX? LEFT_TO_RIGHT : RIGHT_TO_LEFT); // ought to do it.
            arity_from = arity_to = 1;

        }

        // binary infix (left or right associative)
        Operator::Operator( wstring op, BinaryFunction apply, OperatorAssociativity assoc ) 
        : op({op}), unit_f(unit_dummy), unary_f(unary_dummy), binary_f(apply), nary_f(nary_dummy) 
        {
            t = INFIX;
            associativity = assoc;
            arity_from = arity_to = 2;
        }

        // n-ary pre- or post- fix.
        Operator::Operator( wstring op, NAryFunction apply,  OperatorType t)
        : op({op}), t(t), unit_f(unit_dummy), unary_f(unary_dummy), binary_f(binary_dummy), nary_f(apply) 
        {
            arity_from = 0;
            arity_to = SIZE_MAX;
        }

        /// Sigh. Ternary, etc.
        Operator::Operator( vector<wstring> ops, size_t arity, NAryFunction apply, OperatorType t) 
        : op(ops), t(t), unit_f(unit_dummy), unary_f(unary_dummy), binary_f(binary_dummy), nary_f(apply) 
        {

            arity_from = arity_to = arity;
        }

        void Operator::serialize_to( std::ostream &out ) const {
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            out << rhizome_type() << " ";
            if(arity_from != arity_to ) {
                if( arity_to==SIZE_MAX ) {
                    out << arity_from << "," << "∞" << "-compound";
                } else {
                    out << arity_from << "," << arity_to << "-compound";
                }
                
            } else {
                if( arity_from==2 ) {
                    out << "binary";
                } else if( arity_from==1 ) {
                    out << "unary";
                } else if( arity_from==0 ) {
                    out << "unit";
                } else if( arity_from==3 ) {
                    out << "ternary";
                } else {
                    out << arity_from << "-ary";
                }
            }
            out << " ";

            switch(t) {
                case PREFIX: out << "prefix "; break;
                case INFIX: out << "infix subex "; break;
                case POSTFIX: out << "postfix "; break;
                case NONFIX: break;
            }
            
            for(auto i=op.begin(); i!=op.end(); i++ ) {
                wstring w = *i;
                out << converter.to_bytes(w);
                if( (i+1)!=op.end() ) {
                    out << " subex ";
                }
            }
            if( t!=NONFIX ) {
                out << " subex";
            }
            out << " ⏹";
        }

        string
        Operator::rhizome_type() const {
            return "Operator";
        }

        Thing * 
        Operator::clone() const {
            Operator *p = new Operator();
            p->arity_from = arity_from;
            p->arity_to = arity_to;
            p->associativity = associativity;
            p->op = op;
            p->t = t;
            return p;
        }

        bool
        Operator::has_interface( string const &w ) {
            return (w==rhizome_type()||w=="Thing");
        }


        Thing *
        Operator::invoke( string const &method, Thing *arg ) {
            (void)arg;
            if(method=="`"||method=="eval") {
                
            }
            throw runtime_error("Not implemented.");
        }

        
    }
}