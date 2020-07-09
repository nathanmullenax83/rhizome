#include "store_demo.hpp"

using rhizome::words::Dictionary;

namespace rhizome {
    namespace demo {
        void store_demo() {
            static Log log("demos",false);
            Lexer *l = new Lexer();
            Parser *p = new Parser(l);
            Store s(".rhizome",p);
            Dictionary *dict = new Dictionary();

            Table *table = new Table();
            table->set( "un", new rhizome::types::String("Nathan"));
            table->set( "pw", new rhizome::types::String("password"));
            dict->id("Hello");
            dict->id("world");
            dict->update_table();
            
            // relinquishing ownership of pointer here.
            s.set( "user", table );
            s.set( "user.dict", dict );

            rhizome::types::String *hi = new rhizome::types::String("Hello world!");
            s.set( "hi", hi);
            s.serialize_to( 0,std::cout );
        }
    }
}