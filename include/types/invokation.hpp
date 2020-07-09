#ifndef RHIZOME_TYPES_INVOKATION
#define RHIZOME_TYPES_INVOKATION
#include <string>
#include "core/thing.hpp"
#include "types/statement.hpp"
#include "types/expression.hpp"
using std::string;
using rhizome::core::Thing;
using rhizome::core::Dispatcher;
using rhizome::types::Statement;


namespace rhizome {
    namespace types {

        class Invokation: public Statement {
        private:
            Thing *target;
            string method_name;
            Expression *arg;
        public:
            /// @param{target} is any Thing. You own the pointer.
            /// @param{method_name} is the name to be passed into invoke on target.
            /// @param{arg} is an expression to be evaluated before invokation. I own the pointer.
            Invokation( Thing *target, string const &method_name, Expression *arg);
            virtual ~Invokation();

            // statement interface
            virtual Thing * evaluate( Thing *context ) override;

            // thing interface
            virtual string rhizome_type() const override;
            virtual void serialize_to( size_t indent, std::ostream &out ) const override;
            virtual bool has_interface( string const &name );
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;

            /// target is not cloned.
            virtual Thing * clone() const override;

        };
    }
}

#endif