#include "dungeon.hpp"

using rhizome::ui::Console;
using rhizome::types::Tuple;
using rhizome::types::Timeline;
using rhizome::types::Time;
using rhizome::store::Store;
using rhizome::parse::Parser;
using rhizome::lex::Lexer;

namespace P = rhizome::pattern;
namespace G = rhizome::parse;

namespace rhizome {
    namespace demo {
        

        // This one is for deserializing a saved game state
        Parser * create_dungeon_offline_parser() {
            // use default parser.
            return new Parser();
        }

        void columns_axis(Console &console) {
            console <<     "  0 1 2 3 4 5 6 7 8 9 a b c d e f g h i j k l m n o p q r s t u v w x y z \n";
        }

        void castle( Console &console,size_t floors, size_t water_tower ) {
            (void)water_tower;
            columns_axis(console);
            console <<     "A       ▐▟▟▟▟▟▟▟▟▟▟▟▟                 ☁️              " << "\n";
            console <<     "B ▐▟▟▟▟  ███████████▍  ▐▟▟▟▟                ☁️        " << "\n";
            console <<     "C  █🗔 ▍  ████  ██🗔 █▍   █🕱█▍                  ██████ " << "\n";
            console <<     "D  ███▙▃▃████  █████▙▃▃▃███▍                  █    █ " << "\n";
            console <<     "E  ██████████░░████████████▍                  █    █ " << "\n";
            string lets = "FGHIJKLMNOPQRSTUVWXY&Z";
            for(size_t i=0; i<floors; ++i) {
                console.putch(lets[i*2]);
                console <<  "  █▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓█▍                  █    █ " << "\n";
                console.putch(lets[i*2+1]);
                console <<  "  ████████████████████████▍                  █    █ " << "\n";
            }
            columns_axis(console);
        }

        void cellar ( Console &console, size_t room_height ) {
            columns_axis(console);
            console <<     "A    ▟░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▙  " << "\n";
            console <<     "B   ▟█░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░█▙  " << "\n";
            console <<     "C  ▟██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██▙ " << "\n";
            console <<     "D ▟███░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░███▙" << "\n";
            string lets = "EFGHIJKLMNOPQRSTUVWXY&Z";
            size_t i;
            for(i=0; i<room_height; ++i) {
                console.putch(lets[i]);
                console << " ████░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░████" << "\n";
            }
            console.putch(lets[i++]);
            console <<     " ███▛                                            ▜███" << "\n";
            console.putch(lets[i++]);
            console <<     " ██▛                                              ▜██" << "\n";
            console.putch(lets[i++]);
            console <<     " █▛                                                ▜█" << "\n";
            console.putch(lets[i++]);
            console <<     " ▛                                                  ▜" << "\n";
            columns_axis(console);
        }

        void cellar_door( size_t row, size_t col, Console &console, bool open ) {
            console.save_cursor_position();
            console.locate(col,row);
            console << (open?"  ":"█▊");
            console.locate(col,row+1);
            console << (open?"  ":"█▊");
            console.locate(col,row+2);
            console << (open?"░░":"");
            console.restore_cursor_position();
        }

        
        void character( Console &console, size_t row, size_t col ) {
            console.save_cursor_position();
            console.locate(col,row);
            console << rhizome::ui::FG_GREEN_ON;
            console << "🕵 ";
            console.locate(col,row+1);
            console << "██";
            console << rhizome::ui::RESET_COLOR;
            console.restore_cursor_position();
        }

        void welcome_screen(Console &console) {
            console.termios_getch(false);
            console.clear();
            console.h1("𝔑hyme ℭastle 𝔇ungeon");
            castle(console,4,2);
            //cellar(console,4);
            character(console, 10, 8);
            

            
            console.termios_getch(false);
        }

        // this lexer/parser pair is for the REPL
        Lexer * create_dungeon_lexer() {
            Lexer *lexer = new Lexer();
            // create a lexer rule that ignores whitespace
            // except in that is updates the lexer's line-count fields.
            lexer->define_ignore_whitespace();
            
            
            return lexer;
        }

        Parser * create_dungeon_parser(Store *game) {
            Parser *parser = new Parser(create_dungeon_lexer());


            (void)game;
            return parser;
        }

        void choose_character_class( Console &console, Store *game ) {
            rhizome::ui::Menu menu;
            
            menu.add_item("Mucaro",[game](){
                game->set("cclass", new rhizome::types::String("Mucaro"));
            });
            menu.add_item("Spider", [game](){
                game->set("cclass", new rhizome::types::String("Spider"));
            });
            menu.add_item("Programmer",[game](){
                game->set("cclass", new rhizome::types::String("Programmer"));
            });
            menu.choose(console,true);
        }

        Timeline * create_plausible_timeline( Store *context ) {
            Timeline *t = new Timeline(Time(1983,12,29),Time(2020,11,1), context );
            t->schedule( Time(2019,12,14), []( Thing *context, Time t ) {
                (void)t;
                // context here is a store
                Store *store = (Store*)context;
                store->set("Last Event", new String("Happy Anniversary!"));

            });
            t->schedule( Time(2018,12,15), []( Thing *context, Time t ){
                (void)t;
                Store *store = (Store*)context;
                store->set("Last Event", new String("Happy Birthday, Ivy!"));
            });
            return t;
        }

        void dungeon() {
            Console console(std::cout);
            

            // This should load any data from last time. It will create
            // an appropriate folder if it doesn't exist.
            Store *game_context = new Store(".dungeon",create_rhizome_parser());
            Parser *parser = create_dungeon_parser(game_context);
            
            welcome_screen(console);
            choose_character_class(console, game_context);
            cellar(console,4);
            console.termios_getch(false);

            delete parser;
            delete game_context;

        }
    }
}