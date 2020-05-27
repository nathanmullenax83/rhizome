#ifndef RHIZOME_CORE_UNIVERSE_HPP
#define RHIZOME_CORE_UNIVERSE_HPP

#include "thing.hpp"
#include "system.hpp"
#include "i_store.hpp"


namespace rhizome {
    namespace core {
        // provide functions to construct default machine to system.
        System * create_system( IParser *parser, IStore *store );

    }
}

#endif