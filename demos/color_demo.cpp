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
                        return (hd(a)*16 + hd(b))/256.0;
                    };
                    c->r =  hv( s[1], s[2]) ;
                    c->g =  hv( s[3], s[4]) ;
                    c->b =  hv( s[5], s[6]) ;
                    return c; 

                }));
        }
        

        IParser * create_parser() {
            rhizome::parse::Parser *parser = new rhizome::parse::Parser();
            tt_rgb_triple(parser);
            
            parser->rule( "RGBColor", 
                apply(seq(
                    lit("RGB"),
                    match_type("Decimal"),
                    match_type("Decimal"),
                    match_type("Decimal")
                ), []( deque<Thing*> ts ) {
                    rhizome::types::Float *red = (Float*)ts[1];
                    rhizome::types::Float *green = (Float*)ts[2];
                    rhizome::types::Float *blue = (Float*)ts[3];
                    return (Thing*) (new rhizome::types::Color(red->get_value(),green->get_value(),blue->get_value(),1.0));;
                })
            );

            parser->rule( "RGBHexTriple",
                apply( match_type("Color"), [](deque<Thing*> ts) {
                    return ts[0];
                })
            );

            parser->rule( "Start", 
                options({non_term("RGBHexTriple"),non_term("RGBColor")})
            );

            return parser;
        }

        void color_demo() {
            IParser *parser = create_parser();
            IStore *store = new rhizome::store::Store(".colors",parser);
            rhizome::core::System * csystem = rhizome::core::create_system( parser, store );
            
            
            std::cout << "==============\n";
            std::cout << "| Color Demo |\n";
            std::cout << "==============\n";
            
            std::cout << "Enter a color \"RGB n n n\":\n";
            stringstream co;
            string line;
            std::getline( std::cin, line );
            std::getline( std::cin, line );
            co << line;
            parser->q_stream(co);
            Thing * color = parser->parse_thing("Start");
            delete csystem;
            color->serialize_to(std::cout);

            
            vector<Color> cs;
            std::cout << "Hex\t\tIntensity\t\tDec\t\tHue" << std::endl;
            for(size_t i=0; i<10; ++i) {
                Color c;
                c.randomize();
                cs.push_back(c);
                std::cout << c.hex() << "\t\t" << c.intensity() << "\t\t" << c <<
                    "\t\t" << c.hue() << "\t\t" << std::endl;
            }
            

        }
    }
}