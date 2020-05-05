#ifndef RHIZOME_CORE_I_FUNCTION
#define RHIZOME_CORE_I_FUNCTION

#include <vector>
#include "thing.hpp"
#include "i_store.hpp"
#include "i_time.hpp"

using std::vector;
using rhizome::core::ITime;
using rhizome::core::IStore;

namespace rhizome {
    namespace core {

        /// Interface for processes.
        class IFunction {
        public:
            /// Bind one function parameter.
            virtual void bind( string const &param, Thing *value ) = 0;

            /// Derive a new Thing of remaining unbound parameters. 
            virtual Thing * closure() = 0;

            /// These functions are the system-idle process.
            /// Please observe:
            /// 1. if activation falls 
            virtual Thing * tick(ITime *now, double activation_energy)=0;

        };
    }
}

#endif
