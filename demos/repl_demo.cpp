#include "repl_demo.hpp"

#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <functional>
#include "core/thing.hpp"
#include "core/machine.hpp"
#include "parse.hpp"
#include "types.hpp"



using std::string;
using std::stringstream;
using std::function;

using rhizome::core::Thing;
using rhizome::core::Machine;
using rhizome::parse::Parser;
using rhizome::types::Tuple;
using namespace rhizome::parse;


// L( statements+ ) <---
// statement -> << state change >> 

namespace rhizome {
    namespace demo {
        string to_string( Thing *t ) {
            stringstream ss;
            t->serialize_to(ss);
            return ss.str();
        }

        void dump( string prompt, deque<Thing*> ts ) {
            std::cout << prompt << ": ";
            for(size_t i=0; i<ts.size();++i) {
                ts[i]->serialize_to(std::cout);
                std::cout << "\n";
            }
        }

        IParser * create_parser() {
            Parser *p = new Parser();
            
            p->rule("Repl", non_term("Create"), []( deque<Thing*> ts ) {
                dump("Repl",ts);
                return ts[1];
            });
            p->rule("Create",seq(lit("create"), non_term("ObjectName")),[]( deque<Thing*> ts ) {
                dump("Create",ts);
                return ts[1];
            });
            p->rule("ObjectName", match_type("String"),[]( deque<Thing*> ts ){
                dump("ObjectName",ts);
                string tname = to_string(ts[0]);
                if( tname == "Parser" ) {
                    return (Thing*)(new Parser());
                } else if( tname == "Machine") {
                    return (Thing*)(new Machine());
                } else {
                    return (Thing*)(new Tuple());
                }
            });
            return p;
        }

        void repl_demo() {
            
            IParser *parser = create_parser();
            string line;

            while( std::getline( std::cin, line )) {
                if( line != "" ) {
                    stringstream ss;
                    ss << line;
                    parser->q_stream(ss);
                    Thing * result = parser->parse_thing( "Repl");
                    result->serialize_to(std::cout);
                    std::cout << "\n";
                }
                std::cout << "> ";
            }
        }
    }
}