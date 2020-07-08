#include "color_demo.hpp"

using namespace rhizome::parse;
using namespace rhizome::types;

namespace rhizome {
    namespace demo {
        /// Create a token type for RGB hex triples of the for #EF3423
        void tt_rgb_triple( IParser *p ) {
            p->get_lexer()->define_token_type(
                "HexTriple", 
                new rhizome::pattern::Transform(
                new rhizome::pattern::Cat(
                    new rhizome::pattern::Literal("#"),
                    new rhizome::pattern::NTimes(6,new rhizome::pattern::HexDigit())
                ), [](Thing *t){
                    Color *c = new Color();
                    string s = ((String*)t)->native_string();
                    auto hd = []( char c ) { 
                        if ( isdigit(c)) return c - '0';
                        if( isupper(c)) return c - 'A';
                        return c - 'a';
                    };
                    auto hv = [hd]( char a, char b) {
                        double channel = (16*((double)hd(a))) + hd(b);
                        return channel/256.0;
                    };
                    c->r =  hv( s[1], s[2]) ;
                    c->g =  hv( s[3], s[4]) ;
                    c->b =  hv( s[5], s[6]) ;
                    return c; 

                }));
        }
        

        IParser * create_parser(IStore *store) {
            rhizome::parse::Parser *parser = new rhizome::parse::Parser();
            tt_rgb_triple(parser);
            
            parser->rule( "RGBColor", 
                gx_apply(gx_sequence({
                    gx_literal("RGB"),
                    gx_match_type("Decimal"),
                    gx_match_type("Decimal"),
                    gx_match_type("Decimal")
                }), [store]( deque<Thing*> ts ) {
                    rhizome::types::Float *red = (Float*)ts[1];
                    rhizome::types::Float *green = (Float*)ts[2];
                    rhizome::types::Float *blue = (Float*)ts[3];
                    rhizome::types::Color *color = (new rhizome::types::Color(red->get_value(),green->get_value(),blue->get_value(),1.0));
                    store->set("custom_color",color);
                    return (Thing*) color->clone();
                })
            );

            parser->rule( "RGBHexTriple",
                gx_apply( gx_match_type("Color"), 
                    [store](deque<Thing*> ts) {
                        store->set("custom_color",ts[0]);
                        return (Thing*) ts[0]->clone();
                    }
                )
            );

            parser->rule( "Start", 
                gx_options({
                    gx_non_terminal("RGBHexTriple"),
                    gx_non_terminal("RGBColor")
                })
            );

            return parser;
        }

        void color_demo() {
            rhizome::core::System * csystem = rhizome::plant(".color");
            
            
            rhizome::ui::Console console(std::cout);
            console.termios_getch(false);

            console.h1("Color Demo");
            
            std::cout << "Enter a web color #xxxxxx:\n";
            stringstream co;
            string line;
            
            std::getline( std::cin, line );
            co << line;
            try {
                csystem->get_parser()->q_stream(co);
                Thing * color = csystem->parse_thing("Start");
                color->serialize_to(std::cout);
                if( color->has_interface("expression")) {
                    Thing *ev = color->invoke(NULL,"evaluate",NULL);
                    ev->serialize_to(std::cout);
                    std::cout << "\n";
                    delete ev;
                }
                delete csystem;
            } catch (std::exception *e ) {
                stringstream err;
                err << "Error attempting to parse line:\n";
                err << "    \"" << line << "\"\n";
                ((Parser*)csystem->get_parser())->dump(err);
                throw runtime_error(err.str());
            }
            
            vector<Color> cs;
            std::cout << "Hex\t\tIntensity\t\tDec\t\tHue" << std::endl;
            for(size_t i=0; i<10; ++i) {
                Color c;
                c.randomize();
                cs.push_back(c);
                std::cout << c.hex() << "\t\t" << c.intensity() << "\t\t" << c <<
                    "\t\t" << c.hue() << "\t\t" << std::endl;
            }
            
            console.termios_getch(false);
        }
    }
}