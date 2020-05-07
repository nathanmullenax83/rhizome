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
            std::cout << prompt << " (";
            for(size_t i=0; i<ts.size();++i) {
                ts[i]->serialize_to(std::cout);
                std::cout << " ";
            }
            std::cout << ")\n";
        }

        /// Numeric expression interpreters
        void numeric_interpreter( string const &name,Parser *p ) {
            Gramex * term_op = options({lit("+"),lit("-")});
            Gramex * factor_op = options({lit("*"),lit("/")});
            Gramex * summation = seq( non_term("Term"), star( seq(term_op, non_term("Term"))));
            Gramex * product = seq( non_term("Factor"), star( seq(factor_op, non_term("Factor"))));
            Gramex * factor = match_type("Integer");

            p->rule("Factor",apply(factor,[](deque<Thing*> ts){
                std::cout << "Parsing factor: ";
                dump("Factor (ts) = ",ts);
                ts[0]->serialize_to(std::cout);
                std::cout << "\n";
                return ts[0];
            }));
            p->rule("Term", apply(product,
                    [](deque<Thing*> ts){

                        std::cout << "Parsing term\n";
                        dump("Term (ts) = ",ts);
                        rhizome::types::Integer p(1);
                        p = (*((rhizome::types::Integer*)ts[0]));
                        for(size_t i=1; i<ts.size(); i+=2) {
                            if( to_string(ts[i])=="*" ) {
                                p = p * (*((rhizome::types::Integer*)ts[i+1]));
                            } else if ( to_string(ts[i])=="/")  {
                                p = p / (*((rhizome::types::Integer*)ts[i+1]));
                            } else {
                                ts[i]->serialize_to(std::cerr);
                                throw runtime_error("Invalid operator.");

                            }
                        }
                        return p.clone();
                    }) );

            p->rule(name, 
                apply(
                    summation,
                    [](deque<Thing*> ts){
                        std::cout << "Parsing expression\n";
                        dump("Expression (ts) = ", ts);
                        rhizome::types::Integer sum(0);
                        sum = (*((rhizome::types::Integer*)ts[0]));
                        for(size_t i=1; i<ts.size()-1; i+=2) {
                            if( to_string(ts[i])=="+" ) {
                                sum = sum + (*((rhizome::types::Integer*)ts[i+1]));
                            } else {
                                sum = sum - (*((rhizome::types::Integer*)ts[i+1]));
                            }
                        }
                        return sum.clone();
                    }
                )
            );

            

            
        }

        IParser * create_parser() {
            Parser *p = new Parser();
            
            numeric_interpreter("NumericExpression",p);
            p->rule("Repl", options({
                apply(seq(lit("PRINT"), 
                    non_term("NumericExpression")
                ),[](deque<Thing*> ts){
                    ts[1]->serialize_to(std::cout);
                    return (Thing*)(new Tuple());
                })
            }));

            
            return p;
        }

        void repl_demo() {
            
            IParser *parser = create_parser();
            string line;
            
            ((Parser*)parser)->dump(std::cout);



            while( std::getline( std::cin, line )) {
                try {
                    if( line != "" ) {
                        stringstream ss;
                        ss << line;
                        parser->q_stream(ss);
                        Thing * result = parser->parse_thing( "Repl");
                        delete result;
                        
                        std::cout << "\nREADY.\n";
                    }
                    std::cout << "> ";
                } catch ( std::runtime_error *e ) {
                    std::cout << "Error: " << e->what() << "\n";
                    ((Parser*)parser)->dump(std::cout);
                }
            }
        }
    }
}