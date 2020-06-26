#include "plank.hpp"
#include <iostream>
#include "rhizome.hpp"

using rhizome::ui::Console;
using rhizome::ui::Menu;
using rhizome::store::Store;
using rhizome::core::Thing;


namespace rhizome {
    namespace demos {
        Parser *create_parser() {
            Parser *p = new Parser();
            return p;
        }

        void plank() {
            Console console(std::cout);
            Parser *parser = create_parser();
            Menu menu;

            Store s("knitters_point",parser);
            menu.add_item("Party?", [&s](){
                Thing *orgs = s.retrieve("organizations");
                (void)orgs;
            });
            menu.add_item("Publication?", [&s](){
                Thing *pubs = s.retrieve("publications");
                (void)pubs;
            });
            menu.add_item("Services?", [&s](){
                Thing *services = s.retrieve("services");
                (void)services;
            });
            menu.choose(console);
        }
    }
}

