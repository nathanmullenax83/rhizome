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
#include "ui.hpp"

using std::string;
using std::stringstream;
using std::function;

using rhizome::core::Thing;
using rhizome::core::Machine;
using rhizome::parse::Parser;
using rhizome::types::Tuple;
using rhizome::types::Integer;
using rhizome::types::Operator;
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
                if( ts[i]!=NULL ) {
                    ts[i]->serialize_to(std::cout);
                } else {
                    std::cout << "=--------> NULL\n";
                }
                std::cout << " ";
            }
            std::cout << ")\n";
        }

        /// Numeric expression interpreters
        void numeric_interpreter( string const &name,Parser *p, map<string,Thing*> &vars ) {
            Gramex * term_op = options({lit("+"),lit("-")});
            Gramex * factor_op = options({lit("*"),lit("/")});
            Gramex * summation = seq( non_term("Term"), star( seq(term_op, non_term("Term"))));
            Gramex * product = seq( non_term("Factor"), star( seq(factor_op, non_term("Factor"))));
            Gramex * factor = options({
                match_type("Integer"),
                apply(match_lexer_rule("Bareword"),[&vars]( deque<Thing*>ts ){
                    assert(ts.size()==1);
                    String *name = (String*)ts[0];
                    if( vars.count(name->native_string())==0){
                        stringstream err;
                        err << "Variable '" << name->native_string() <<"' is not defined!";
                        throw runtime_error(err.str());
                    }
                    return vars[name->native_string()];
                })
            });

            p->rule("Factor",apply(factor,[](deque<Thing*> ts){
                //std::cout << "Parsing factor: ";
                //dump("Factor (ts) = ",ts);
                assert( ts.size()==1 && ts[0]!=NULL );
                return ts[0];
            }));
            p->rule("Term", apply(product,
                    [](deque<Thing*> ts){

                        //std::cout << "Parsing term\n";
                        //dump("Term (ts) = ",ts);
                        rhizome::types::Integer q(1);
                        q = (*((rhizome::types::Integer*)ts[0]));
                        for(size_t i=1; (i+1)<ts.size(); i+=2) {
                            if( to_string(ts[i])=="*" ) {
                                assert( ts[i+1]->rhizome_type()=="Integer");
                                q = q * (*((rhizome::types::Integer*)ts[i+1]));
                            } else if ( to_string(ts[i])=="/")  {
                                assert( ts[i+1]->rhizome_type()=="Integer");
                                q = q / (*((rhizome::types::Integer*)ts[i+1]));
                            } else {
                                ts[i]->serialize_to(std::cerr);
                                throw runtime_error("Invalid operator.");

                            }
                        }
                        return q.clone();
                    }) );

            p->rule(name, 
                apply(
                    summation,
                    [](deque<Thing*> ts){
                        //std::cout << "Parsing expression\n";
                        //dump("Expression (ts) = ", ts);
                        assert( ts.size() > 0);
                        rhizome::types::Integer sum(0);
                        assert( ts[0]->rhizome_type()=="Integer");
                        sum = (*((rhizome::types::Integer*)ts[0]));
                        
                        for(size_t i=1; (i+1)<ts.size(); i+=2) {
                            if( to_string(ts[i])=="+" ) {
                                assert( ts[i+1]->rhizome_type()=="Integer");
                                sum = sum + (*((rhizome::types::Integer*)ts[i+1]));
                            } else {
                                assert( ts[i+1]->rhizome_type()=="Integer");
                                sum = sum - (*((rhizome::types::Integer*)ts[i+1]));
                            }
                        }
                        return sum.clone();
                    }
                )
            );

            

            
        }

        typedef map<string, function< Thing *(Thing*)> > CtorTable;

        IParser * create_parser( CtorTable &ctors, bool &quit, rhizome::ui::Console &console, map<string, Thing*> &vars ) {
            Parser *p = new Parser();
            
            numeric_interpreter("NumericExpression",p, vars);

            p->rule("Repl", seq(non_term("Expr"), star(seq(lit(":"), non_term("Expr")))));

            p->rule("Expr", options({
                apply(seq(lit("PRINT"), 
                    non_term("NumericExpression")
                ),[](deque<Thing*> ts){
                    ts[1]->serialize_to(std::cout);
                    return (Thing*)(new Tuple());
                }),
                apply(seq(lit("CREATE"), non_term("ThingSpec")),[&ctors](deque<Thing*> ts){
                    return ts[1];
                }),
                apply(options({lit("END"),lit("QUIT")}), [&quit](deque<Thing*> ts) {
                    (void)ts;
                    quit = true;
                    return (Thing*)(new Tuple());
                }),
                apply(lit("CLS"),[&console](deque<Thing*> ts){
                    (void)ts;
                    console.clear();
                    return (Thing*)(new Tuple());
                }),
                
                apply(
                    seq(
                        lit("LOCATE"),
                        non_term("NumericExpression"),
                        lit(","),
                        non_term("NumericExpression")),
                        [&console](deque<Thing*>ts){
                            Integer *row = (Integer*)ts[1];
                            Integer *col = (Integer*)ts[3];
                            console.locate(col->native_int(),row->native_int());
                            return new Tuple();
                        }),
                apply(seq(match_type("String"),lit("="),non_term("NumericExpression")),[&vars](deque<Thing*> ts){
                    String *vname = (String*)ts[0];
                    vars[vname->native_string()] = ts[2];
                    for(size_t i=0; i<ts.size()-1; ++i) {
                        if( ts[i]!=NULL) { delete ts[i]; }
                    }
                    return (Thing*)(new Tuple());
                })
            }));

            

            p->rule("ThingSpec", apply(seq(match_type("Bareword"), non_term("Tuple")),
            [&ctors](deque<Thing*> ts){
                std::cout << "Matched rule ThingSpec.\n";
                auto stringify = []( Thing *t ) { stringstream ss; t->serialize_to(ss); return ss.str(); };
                string name = stringify( ts[0] );
                return (Thing*)ctors[name](ts[1]);
            }));

            p->rule("Tuple", apply(seq(match_type("OParen"),match_type("CParen")), [](deque<Thing*> ts) {
                (void)ts;
                return new Tuple();
            }));
            
            return p;
        }

        void repl_demo() {
            rhizome::ui::Console console(std::cout);

            CtorTable ctors;
            ctors["Str"] = []( Thing *arg ) {
                std::cout << "String ctor.\n";
                stringstream ss;
                arg->serialize_to(ss);
                String *s = new String(ss.str());
                return (Thing*)s;
            };
            
            map<string, Thing *> vars;

            bool quit = false;
            IParser *parser = create_parser(ctors, quit, console, vars);
            string line;
            
            ((Parser*)parser)->dump(std::cout);
            std::cout << "\n";

            
            while( (!quit) && std::getline( std::cin, line )) {
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