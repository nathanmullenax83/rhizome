#include "invokation.hpp"

namespace rhizome
{
    namespace types
    {
        namespace invokation
        {
            static Dispatcher<Invokation> dispatcher({
                {
                    "evaluate", [](Thing *context, Invokation *that, Thing *arg) {
                        (void)context;
                        return that->evaluate(arg);
                }
            }});
        }

        Invokation::Invokation(Thing *target, string const &method_name, Expression *arg)
            : target(target), method_name(method_name), arg(arg)
        {
        }

        Invokation::~Invokation()
        {
            delete arg;
        }

        string
        Invokation::rhizome_type() const
        {
            return "Invokation";
        }

        void
        Invokation::serialize_to(std::ostream &out) const
        {
            out << rhizome_type() << "{\n";
            out << "    target: ";
            target->serialize_to(out);
            out << "\n";
            out << "    arg: ";
            arg->serialize_to(out);
            out << "\n";
            out << "}\n";
        }

        bool
        Invokation::has_interface(string const &name)
        {
            return name == "Thing" || name == rhizome_type() || name == "statement";
        }

        Thing *
        Invokation::clone() const
        {
            Invokation *inv = new Invokation(target, method_name, (Expression*)arg->clone());
            return inv;
        }

        Thing *
        Invokation::invoke(Thing *context, string const &method, Thing *arg)
        {
            try
            {
                return invokation::dispatcher.at(method)(context, this, arg);
            }
            catch (std::exception *e)
            {
                if (invokation::dispatcher.count(method) == 0)
                {
                    throw(rhizome::core::invoke_method_not_found(method, this, context));
                }
                else
                {
                    throw(rhizome::core::invoke_error(method, arg, this, context, e));
                }
            }
        }

        Thing *
        Invokation::evaluate(Thing *context)
        {
            return target->invoke(context, method_name, arg);
        }
    } // namespace types

} // namespace rhizome