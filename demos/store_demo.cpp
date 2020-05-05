#include "store_demo.hpp"

namespace rhizome {
    namespace demo {
        void store_demo() {
            static Log log("demos",false);
            Store s(".rhizome");

            Table *table = new Table();
            table->set( "un", new rhizome::types::String("Nathan"));
            table->set( "pw", new rhizome::types::String("password"));
            
            // relinquishing ownership of pointer here.
            s.set( "user", table );

            rhizome::types::String *hi = new rhizome::types::String("Hello world!");
            s.set( "hi", hi);
            s.serialize_to( std::cout );
        }
    }
}