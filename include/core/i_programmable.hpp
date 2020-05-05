#ifndef RHIZOME_CORE_I_PROGRAMMABLE
#define RHIZOME_CORE_I_PROGRAMMABLE

#include <functional>
#include <deque>
#include "thing.hpp"

using std::function;
using std::deque;
using rhizome::core::Thing;

namespace rhizome {
    namespace core {
        /// Anything that can be programmed using an internal assembly language
        /// is 'IProgrammable'
        
        class IProgrammable {
        private:
            // A deque, so we can make generators easily
            deque<Thing*> data;
        public:
            // make sure we can 'delete' using an IProgrammable pointer.
            virtual ~IProgrammable() {}


            virtual Thing* invoke( string const &operation, Thing *arg ) = 0;

        };

        /* The gist:
           Every class defines a kind of sublanguage that can be almostly trivially implemented. 
           The instructions are simply methods. Some classes already implement scripting in this
           way, and do so by way of an easy-to-parse assembly language, representing core
           operations on the type corresponding to a class.

           Implementation details:
           I'm a little torn between templates and interfaces here. 

           The template option looks clean:
            Machine<Type> machine;
            machine.push(Type t);
            ...
           
           Unresolved: division of integers could produce either a fraction or a decimal. The
           integer machine must be able to identify the fraction (or decimal) machine with
           witch to manipulate the result. This requires the Integer class to have 'an awareness'
           of class that comprises it.

           Compromise: abstract interfaces can be referenced by the whole suite of types. 


         */
    }
}

#endif