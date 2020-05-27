#include "universe.hpp"

namespace rhizome {
    namespace core {
        /// Create default system -- parser is configured with 
        /// constructors. Storage is rooted in some directory. 
        System *create_system( IParser *parser, IStore *store ) {
            System *s = new System(parser,store);
            return s;
        }
    }
}