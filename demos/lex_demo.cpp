#include "lex_demo.hpp"

using rhizome::lex::Token;
using rhizome::core::Machine;
using rhizome::core::System;
using rhizome::store::Store;

namespace rhizome {
    namespace demo {

        bool test_unicode() {
            rlex::Lexer lexer;

            // special tokens can construct core objects
            lexer.define_token_type( "☭Store", new rhizome::pattern::Literal("☭System"),[](void){
                return (Thing*)new Store(".rhizome");
            });

            lexer.define_token_type( "☭Parser", new rhizome::pattern::Literal("☭Parser"),[](void){
                return (Thing*)new Parser();
            });

            lexer.define_token_type( "☭Machine", new rhizome::pattern::Literal("☭Machine"),[](void){
                return (Thing*)new Machine();
            });

            // special tokens can manipulate the lexer


            // ignore whitespace rule.
            std::cout << "Defining whitespace rule...\n";
            lexer.define_token_type( "WS", new rhizome::pattern::Whitespace(), [](void){
                return (Thing*)NULL;
            });
            std::cout << "Preparing unicode test...\n";
            stringstream test;
            test << "☭Parser ☭Machine";

            
            try {
                lexer.q(test);
                while( lexer.has_next_thing() ){
                    Thing *t = lexer.next_thing();
                    std::cout << "Extracted: ";
                    t->serialize_to(std::cout);
                    std::cout << "\n";
                }
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

        void lex_demo() {
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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            lexer.define_token_type( "whitespace", new rp::Group(new rp::Plus( new rp::Whitespace())),
                []( IToken *t) {
                    
                    return (Thing*)NULL;
                });
#pragma GCC diagnostic pop

            vector<string> kws({"for","next","then","if","else","end","each"});
            lexer.define("keyword",kws);

            stringstream example;
            example << "for each if then else";
            lexer.q(example);

            while( lexer.has_next_thing()) {
                Thing *temp = lexer.next_thing();
                
                std::cout << "'";
                temp->serialize_to(std::cout);
                std::cout << " - ";
                std::cout << temp->rhizome_type() << '\n';
                delete temp;
            }

            std::cout << "Attempting to put back a few things: \n";
            lexer.put_back_thing( new rhizome::types::Integer(5));
            lexer.put_back_thing( new rhizome::types::String("Hello world."));
            Thing *X = lexer.peek_next_thing(0);
            Thing *Y = lexer.peek_next_thing(1);

            Thing *x = lexer.next_thing();
            Thing *y = lexer.next_thing();
            x->serialize_to(std::cout); std::cout << '\n';
            y->serialize_to(std::cout); std::cout << '\n';
            X->serialize_to(std::cout); std::cout << '\n';
            Y->serialize_to(std::cout); std::cout << '\n'; 
            
#ifdef INSTRUMENTED
            log.info("Lexing demo ended normally.");
#endif
        }
    }
}