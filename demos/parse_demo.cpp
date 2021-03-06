#include "parse_demo.hpp"

using rhizome::types::Tuple;
using rhizome::types::Integer;
using rhizome::types::String;
using rhizome::types::Table;

using rhizome::parse::Parser;

namespace UI = rhizome::ui;

namespace rhizome {
    namespace demo {

        string test_title( string const &title, Parser *parser ) {
            stringstream f_title;
            f_title << "\033[1m" << title << UI::RESET_COLOR << "\n";
            f_title << string(title.size(),'=') << "\n";
            parser->dump(f_title);
            f_title << "\n";
            return f_title.str();
        }
        
        bool parse_test_star() {
            Parser grammar;
            std::cout << test_title( "Star Closure Test", &grammar);
            grammar.rule( "<start>", 
                gx_apply(
                    gx_star_closure(
                        gx_sequence({
                            gx_literal("A"),
                            gx_literal("B")
                        })
                    ), 
                    [](deque<Thing*> ts){
                        Tuple *t  = new Tuple();
                        for(size_t i=0; i<ts.size(); ++i) {
                            t->append( ts[i] );
                        }
                        return t;
                    }
                )
            );
            grammar.dump(std::cout);
            Thing * result = grammar.parse_thing("<start>", "A B A B");
            std::cout << "Result: ";
            result->serialize_to(1,std::cout);
            std::cout << "\n";
            delete result;
            return true;
        }

        bool TEST_nonterminal() {
            parse::Parser p;
            p.rule("S0", gx_non_terminal("A"));
            p.rule("A", gx_apply(gx_non_terminal("B"), [](deque<Thing*> ts){
                //std::cout << "A production.\n";
                assert(ts.size()==1);
                return ts[0];
            }));
            p.rule("B", gx_literal("C"));
            p.rule("D",gx_apply(gx_non_terminal("A"),[]( deque<Thing*> ts ){
                //std::cout << "D production.\n";
                assert( ts.size()==1);
                return ts[0];
            }));
            
            std::cout << test_title("Non-terminals test",&p);
            stringstream s;
            s << "C";
            p.q_stream(s);
            try {
                Thing *result = p.parse_thing("D");
                result->serialize_to(1,std::cout);
                std::cout << "\n";

                return true;
            } catch( std::exception * e ) {
                return false;
            }

        }

        bool TEST_or() {
            parse::Parser p;
            p.rule("S", gx_options({
                gx_literal("a"),
                gx_literal("b"),
                gx_non_terminal("C")
            }));
            p.rule("C",gx_options({
                gx_literal("d"),
                gx_sequence({gx_literal("e"),gx_star_closure(gx_literal("f"))})
            }));
            std::cout << test_title("Options and non-terminals",&p);
            
            
            stringstream s;
            s << "e";
            p.q_stream(s);                              
            try{
                Thing *result = p.parse_thing("S");
                std::cout << "Result: ";
                result->serialize_to(1,std::cout);
                std::cout << "\n";
                return true;
            }catch(std::exception *e) {
                std::cout << e->what();
                return false;
            }
        }

        bool parse_seq() {
            // test only sequences and literals
            parse::Parser grammar;
            grammar.rule(
                "<start>",
                gx_apply(
                    gx_sequence({
                        gx_sequence({ gx_literal("a"),gx_literal("b")}),
                        gx_literal("c")
                    }),
                    []( deque<Thing*> ts ) {
                        rhizome::types::String *s = new rhizome::types::String();
                        for( size_t i=0; i<ts.size(); ++i) {
                            stringstream ss;
                            ts[i]->serialize_to(0,ss);
                            s->append( ss.str() );
                        }
                        return s;
                    }
                )
            );
            std::cout << test_title("Sequence of Literals", &grammar);
            stringstream test0;
            test0 << "a b c";

            grammar.q_stream(test0);
            Thing * result = grammar.parse_thing( "<start>");

            std::cout << "Result: ";
            result->serialize_to(1,std::cout);
            std::cout << '\n';
            delete result;
            return true;
        }

        bool parse_literal() {
            parse::Parser grammar;
            grammar.rule("Start",gx_apply(gx_literal("START"),[](deque<Thing*>ts){
                rhizome::types::Tuple *t = new rhizome::types::Tuple();
                for(size_t i=0; i<ts.size();++i) {
                    t->append(ts[i]);
                }
                return t;
            }));
            std::cout << test_title("Testing literal match", &grammar);
            
            stringstream test0;
            test0 << "START";
            grammar.q_stream(test0);
            
            Tuple *vs = (Tuple*)grammar.parse_thing("Start");
            
            bool pass = (vs->size()==1);
            for(size_t i=0; i<vs->size(); ++i) {
                vs->at(i)->serialize_to(1,std::cout);
                std::cout <<  "\n";
            }
            return pass;
        }

        bool parse_test_match_type() {
            
            parse::Parser grammar;
            grammar.rule("Start",
                gx_apply(gx_plus_closure(gx_match_type("Int")), [](deque<Thing*> ts){
                Tuple *t = new Tuple();
                for(size_t i=0; i<ts.size(); ++i) {
                    t->append(ts[i]);
                }
                return t;
            }));
            std::cout << test_title("Type Match", &grammar);

            bool pass(true);
            auto debug_print = [&pass]( string const &vname, Thing *t )  {
                std::cout << vname << " = ";
                t->serialize_to(0,std::cout);
                std::cout << "( status = " << (pass?"passing":"failing") << " )";
                std::cout << "\n";
            };

            
            stringstream example;
            example << "54 42 36 25 16";
            grammar.q_stream(example);
            Tuple *vs = (Tuple*)grammar.parse_thing("Start");    
            pass &= (vs->size()==5);
            debug_print("vs", vs );

            stringstream example2;
            example2 << "10 4";
            grammar.q_stream(example2);
            Tuple *vs_also = (Tuple*)grammar.parse_thing("Start");
            pass &= (vs_also->size()==2);
            debug_print("vs", vs_also );
            delete vs;
            delete vs_also;
            return pass;
        }

        bool parse_test_literal_star() {
            parse::Parser grammar;
            grammar.rule("Start",gx_apply(gx_star_closure(gx_literal("A")), [](deque<Thing*> ts){
                Tuple *t = new Tuple();
                for(size_t i=0; i<ts.size(); ++i) {
                    if( ts[i]!=NULL ) {
                        t->append(ts[i]);
                    }
                }
                return t;
            }));
            std::cout << test_title( "Star closure", &grammar);
            

            bool pass(true);
            auto debug_print = [&pass]( string const &vname, Thing *t )  {
                std::cout << vname << " = ";
                t->serialize_to( 0,std::cout);
                std::cout << "( status = " << (pass?"passing":"failing") << " )";
                std::cout << "\n";
            };

            Tuple *vs = (Tuple*)grammar.parse_thing("Start","A A A A A");    
            pass &= (vs->size()==5);
            debug_print("vs", vs );
            Tuple *vs_also = (Tuple*)grammar.parse_thing("Start","A A");
            pass &= (vs_also->size()==2);
            debug_print("vs", vs_also );
            delete vs;
            delete vs_also;
            return pass;
        }

        bool parse_negative_integer() {
            parse::Parser grammar;
            grammar.rule( "S", gx_match_lexer_rule("Int"));
            std::cout << test_title("Single negative integer",&grammar);
            Thing *result = grammar.parse_thing("S", "-567");
            bool pass = true;
            pass = pass && result != NULL;
            pass = pass && result->rhizome_type()=="Int";
            pass = pass && ((rhizome::types::Integer*)result)->native_int()==-567; 

            return pass;
        }

        bool parse_test_list() {
            parse::Parser grammar;
            grammar.rule( "Start",
                gx_apply(gx_sequence({gx_match_lexer_rule("Int"), gx_star_closure(gx_sequence({gx_literal(","),gx_match_lexer_rule("Int")}))}),
                []( deque<Thing*> ts ){
                    rhizome::types::Tuple *tuple = new rhizome::types::Tuple();
                    for( size_t i=0; i<ts.size(); ++i) {
                        if( ts[i]->rhizome_type()=="Int") {
                            tuple->append( ts[i] );
                        }
                    }
                    return tuple;
                }
            )); 
            std::cout << test_title( "Comma delimited list of integers", &grammar);
            bool pass = true;
            stringstream alist;
            alist << "0";
            for(size_t i=1;i<10; ++i) {
                
                std::cout << "\tInput: '" << rhizome::ui::FG_WHITE_ON << alist.str() << rhizome::ui::RESET_COLOR << "'\n";
                rhizome::types::Tuple *vs = (rhizome::types::Tuple*)grammar.parse_thing("Start",alist.str());
                std::cout << "\tOutput: '" << rhizome::ui::FG_GREEN_ON;
                vs->serialize_to(1,std::cout);
                std::cout << rhizome::ui::RESET_COLOR << "'\n";
                pass = pass && (vs->size()==i);
                alist << "," << ((int)(rand()%100)-50);
            }
            
            return pass;
        }

        void parse_demo() {
            rhizome::ui::Console console(std::cout);
            console.termios_getch(false); // eat newline.


            typedef function< bool() > ParseTest;
            vector<ParseTest> tests({
                parse_literal,
                parse_test_literal_star,
                parse_test_match_type,
                parse_seq,
                TEST_nonterminal,
                TEST_or,
                parse_test_star,
                parse_negative_integer,
                parse_test_list
                
            });

            for( auto i=tests.begin(); i!=tests.end();i++) {
                if( i->operator()() ) {
                    std::cout << rhizome::ui::FG_GREEN_ON << "  Success!\n\n" << rhizome::ui::RESET_COLOR;
                } else {
                    std::cout << rhizome::ui::FG_RED_ON << "  Failure!\n\n" << rhizome::ui::RESET_COLOR;
                }
                
            }
            // wait for the any key
            console.termios_getch(false);

        }
    }
}