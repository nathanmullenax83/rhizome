#include "reference_expression.hpp"

using rhizome::core::Dispatcher;

namespace rhizome {
    namespace types {
        namespace refexp {
            static Dispatcher<ReferenceExpression> dispatcher({

            });
        }

        ReferenceExpression::ReferenceExpression(string const &name, TypeConstraint *tc)
        : name(name), reftype(tc) {

        }

        ReferenceExpression::~ReferenceExpression() {
            delete reftype;
        }

        // thing impl
        string 
        ReferenceExpression::rhizome_type() const {
            return "RefExp";
        }

        void
        ReferenceExpression::serialize_to( std::ostream &out ) const {
            out << rhizome_type() << "{\n";
            out << "    name: \"" << name;
            out << "\"\n";
            out << "    type: ";
            reftype->serialize_to(out);
            out << "\n";
            out << "}\n";
        }

        bool
        ReferenceExpression::has_interface( string const &name ) {
            return name=="Thing"||name=="expression"||name==rhizome_type();
        }

        Thing *
        ReferenceExpression::clone() const {
            ReferenceExpression *re = new ReferenceExpression(name,(TypeConstraint*)reftype->clone());
            return re;
        }

        Thing *
        ReferenceExpression::invoke( Thing *context, string const &method, Thing *arg ) {
            try {
                Thing *r =  refexp::dispatcher.at(method)(context,this,arg);
                return r;
            } catch( std::exception *e ) {
                if( refexp::dispatcher.count(method)==0) {
                    throw runtime_error(rhizome::core::invoke_method_not_found(method,this,context));
                } else {
                    throw runtime_error(rhizome::core::invoke_error(method,arg,this,context,e));
                }
            }
        }

        Thing *
        ReferenceExpression::evaluate( Thing *context ) const {
            String *temp = new String(name);
            Thing *deref = context->invoke(context,"get",temp);
            delete temp;
            if( deref->has_interface("expression")) {
                Expression *e = (Expression*)deref;
                Thing *result = e->evaluate(context);
                delete e;
                return result;
            } else {
                Thing *result = deref->clone();
                return result;
            }
        }

    }
}