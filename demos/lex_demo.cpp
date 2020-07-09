#include "lex_demo.hpp"
#include <functional>
#include <vector>
#include "ui.hpp"

using rhizome::lex::Token;

using rhizome::core::System;
using rhizome::store::Store;

using std::function;
using std::vector;

using namespace rhizome::pattern;

namespace rhizome {
    namespace demo {

        bool test_unicode() {
            rlex::Lexer lexer;

            // special tokens can construct core objects
            lexer.define_token_type( "☭Store", new Transform(new rhizome::pattern::Literal("☭System"),[&lexer](Thing* t){
                delete t;
                return (Thing*)new Store(".rhizome", new rhizome::parse::Parser(&lexer));
            }));

            lexer.define_token_type( "☭Parser", new Transform(new rhizome::pattern::Literal("☭Parser"),[](Thing*t){
                delete t;
                return (Thing*)new Parser();
            }));

            

            // special tokens can manipulate the lexer


            // ignore whitespace rule.
            std::cout << "Defining whitespace rule...\n";
            lexer.define_token_type( "WS", new Transform(new rhizome::pattern::Whitespace(), [](Thing*t){
                delete t;
                return (Thing*)NULL;
            }));
            std::cout << "Preparing unicode test...\n";
            stringstream test;
            test << "☭Parser ☭Machine";

            
            try {
                lexer.q(test);
                stringstream captured;
                //std::cout << "Attempting to look ahead.";
                deque<Thing *> parser_NULL_machine = lexer.peek_next_thing(3,false);
                Thing *t_parser = parser_NULL_machine[0];
                
                std::cout << "Parser? " << t_parser->rhizome_type();
                

                
            } catch( std::exception e ) {
                std::cout << "Error extracting tokens. " << e.what() << "\n";
                return false;
            }
            return true; 
        }

        void test_stream_queue() {
            
            rlex::StreamQueue sq;
            stringstream example;
            example << "Concatenating two streams: old stream-->|";
            stringstream example2;
            example2 << "|<-- new stream.";
            sq.q(example);
            sq.q(example2);
            while( !sq.empty() ) {
                std::cout << (char)sq.next() << " ";
            }
            std::cout << std::endl;
        }

        bool test_null_lexer_productions() {
            Lexer l0;
            
            l0.define_token_type("Space", new rhizome::pattern::Transform( new rhizome::pattern::Plus(new rhizome::pattern::Whitespace()),[](Thing* a){
                (void)a;
                return (Thing*)NULL;
            }));
            l0.define_token_type("Word", new rhizome::pattern::Plus( new rhizome::pattern::Alpha()));

            stringstream s;
            s << "this is a test";
            
            l0.q(s);
            //l0.dump(std::cout);

            deque<Thing*> produced;
            bool pass = true;
            while( l0.has_next_thing()) {
                string captured;
                Thing *t = l0.next_thing(captured);
                
                if( t!= NULL ) {
                    produced.push_back(t);
                }
                
                //std::cout << "\n-----\n";
                pass = pass && (t!=NULL);
            }
            if( !pass ) {
                stringstream err;
                err << "Received null productions from 'Lexer::next_thing. This should never happen.\n";
                throw runtime_error(err.str());
            }
            pass = pass && produced.size()==4;
            if( !pass ) {
                stringstream err;
                err << "Lexer produced wrong number of tokens. Expected 4 and got " << produced.size() << "\n";
                throw runtime_error(err.str());
            }
            return pass;
        }

        void lex_demo() {
            vector< function<bool(void)> > tests ({test_null_lexer_productions});
            for( auto i=tests.begin(); i!=tests.end(); ++i) {
                auto f = *i;
                if( f() ) {
                    std::cout << rhizome::ui::FG_GREEN_ON << "Passed\n" << rhizome::ui::RESET_COLOR;
                } else {
                    std::cout << rhizome::ui::FG_RED_ON << "Failed\n" << rhizome::ui::RESET_COLOR;
                }
            }

#ifdef INSTRUMENTED
            static rhizome::log::Log log("demos",false);
            log.info("Lex demo launched.");
#endif
            std::cout << " Lexer demo." << '\n';
            std::cout << "============" << '\n';
            test_stream_queue();

            if( test_unicode() ) {
                std::cout << "Unicode test passed.\n";
            } else {
                std::cout << "Unicode test failed.\n";
            }

            Lexer lexer;

            lexer.define_token_type( "whitespace", new Transform(new rp::Plus( new rp::Whitespace()),
                []( Thing *t) { 
                    (void)t;
                    return (Thing*)NULL;
                }));


            vector<string> kws({"for","next","then","if","else","end","each"});
            lexer.define("keyword",kws);

            stringstream example;
            example << "for each if then else";
            lexer.q(example);

            while( lexer.has_next_thing()) {
                string cap;
                Thing *temp = lexer.next_thing(cap);
                if( temp != NULL ) {
                    std::cout << "'";
                    temp->serialize_to(0,std::cout);
                    std::cout << "' - ";
                    std::cout << temp->rhizome_type() << '\n';
                    delete temp;
                }
            }

            
            

            ILexer *l = rhizome::load_lexer("lexers/http.lexer");
            ((Lexer*)l)->dump(std::cout);
            delete l;
#ifdef INSTRUMENTED
            log.info("Lexing demo ended normally.");
#endif
        }
    }
}