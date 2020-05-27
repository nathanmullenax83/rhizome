#ifndef RHIZOME_CORE_I_STORE_HPP
#define RHIZOME_CORE_I_STORE_HPP

#include <string>
#include "thing.hpp"


using std::string;
using rhizome::core::Thing;

namespace rhizome {
    namespace core {
        /// Named item storage. 
        class IStore {
        public:
            virtual ~IStore() {}
            virtual void set( string const &name, Thing *thing ) = 0;
            virtual Thing * get( string const &name ) = 0;
            virtual Thing * get_clone( string const &name ) const  = 0;
            virtual void remove( string const &name ) = 0;
            virtual bool exists( string const &name ) const = 0;
        };
    }
}

#endif