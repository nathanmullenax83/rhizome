#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "log.hpp"
#include "types.hpp"
#include "ui/menu.hpp"



#include "demos/patterns_demo.hpp"
#include "demos/html_demo.hpp"
#include "demos/http_demo.hpp"
#include "demos/console_demo.hpp"
#include "demos/color_demo.hpp"
#include "demos/types_demo.hpp"
#include "demos/lex_demo.hpp"
#include "demos/parse_demo.hpp"
#include "demos/genesis_demo.hpp"
#include "demos/sdt_demo.hpp"
#include "demos/store_demo.hpp"
#include "demos/machine_demo.hpp"
#include "demos/repl_demo.hpp"
#include "demos/alphabet_demo.hpp"
#include "demos/plank.hpp"
#include "demos/int_ops.hpp"
#include "demos/dungeon.hpp"

using std::string;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"


int main(int argc, char **argv) {
    std::cout << "Running system check...\n";
    bool result = rhizome::verify();
    std::cout << (result?"Passed":"Failed") << "\n";
    srand(time(NULL));
    rhizome::log::Log logger("main-thread-log");
    rhizome::ui::Console c(std::cout);
    c.clear_screen();
    rhizome::ui::Menu menu;
    
    menu.add_item( "\033[1;32mGenesis Demo\033[0m", rhizome::demo::genesis_demo );
    menu.add_item( "Alphabet Demo", rhizome::demo::alphabet_demo );
    menu.add_item( "Types Demo", rhizome::demo::types_demo);
    menu.add_item( "Pattern Tests", rhizome::demo::patterns_demo );

    menu.add_item( "Expression parser", rhizome::demo::color_demo );
    menu.add_item( "HTML Demo", rhizome::demo::html_demo );
    //menu.add_item( "HTTP Demo", rhizome::demo::http_demo );
    menu.add_item( "Console Demo", rhizome::demo::console_demo );
    //menu.add_item( "SDT Demo", rhizome::demo::sdt_demo );
    menu.add_item( "Parsing Tests", rhizome::demo::parse_demo);
    menu.add_item( "Inter-session storage demo", rhizome::demo::store_demo);
    //menu.add_item( "Machine Demo", rhizome::demo::machine_demo );
    menu.add_item( "Dynamic Integer Operators", rhizome::demo::int_ops );
    menu.add_item( "REPL Demo", rhizome::demo::repl_demo );
    //menu.add_item( "Pirates Knitting", rhizome::demos::plank );
    menu.add_item( "Dungeon", rhizome::demo::dungeon);
    //menu.add_item( "Image Demo", rhizome::types::image_demo );
    bool quit = false;
    menu.add_item( "Quit", [&quit](){ quit=true; });

    while(!quit) {
        menu.choose(c);
    }
    
}
#pragma GCC diagnostic pop
