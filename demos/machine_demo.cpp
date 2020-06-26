#include "machine_demo.hpp"
#include "rhizome.hpp"


using rhizome::core::System;
using rhizome::core::Machine;
using rhizome::types::Integer;
using rhizome::types::String;
using rhizome::types::Float;
using rhizome::parse::Parser;
using rhizome::store::Store;

namespace rhizome {
    namespace demo {
        void machine_demo() {
            IParser * parser = new Parser();
            IStore * store = new Store(".rhizome",parser);
            /// parser is by default primed with constructors for basic system types!
            
            // now parser is constructing objects for a particular
            // system. 
            System r(parser,store);

            
            
            
        }
    }
}