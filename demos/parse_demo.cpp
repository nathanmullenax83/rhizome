#include "parse_demo.hpp"

using rhizome::types::Tuple;
using rhizome::types::Integer;
using rhizome::types::String;
using rhizome::types::Table;

namespace rhizome {
    namespace demo {
        

        parse::Parser * create_BASIC_grammar() {
            
            parse::Parser *parser = new parse::Parser();
                parser->rule( 
                    "Program", apply(plus(non_term("Statement")),
                    [](deque<Thing*> ts){
                        Table *t = new rhizome::types::Table();
                        for(size_t i=0; i<ts.size();++i) {
                            Tuple *line = (rhizome::types::Tuple*)ts[i];
                            rhizome::types::Integer *line_no = (rhizome::types::Integer*)line->at(0);
                            rhizome::core::Thing *stmt = line->at(1);
                            stringstream ss;
                            line_no->serialize_to(ss);
                            t->set( ss.str(), stmt );
                        }
                        return t;
                    }));
                parser->rule( 
                    "Statement", 
                        apply(seq(non_term("LineNo"),
                        options({
                            non_term("EndStatement"),
                            non_term("GotoStatement"),
                            non_term("LocateStatement"),
                            non_term("PrintStatement"),
                            non_term("LineStatement"),
                            non_term("InputStatement"),
                            non_term("IfStatement"),
                            non_term("NextStatement"),
                            non_term("ForStatement"),
                            non_term("AssignmentStatement"),
                            non_term("RandomizeStatement"),
                            non_term("ClsStatement"),
                            non_term("ScreenStatement")
                        })),
                []( deque<Thing*> ts ) {
                    rhizome::types::Tuple *t = new rhizome::types::Tuple();
                    assert( ts.size()==2 );
                    t->append( ts[0]);
                    t->append( ts[1]);
                    return t;
                })
                
            );
            parser->rule(
                    "EndStatement",
                    apply(lit("END"),
                    []( deque<Thing*> ts ) {
                        return ts[0];
                    }));
            parser->rule(
                    "ClsStatement",
                    apply(lit("CLS"),
                    []( deque<Thing*> ts ) {
                        return ts[0];
                    }));
            parser->rule(
                    "GotoStatement",
                    apply(seq(lit("GOTO"),non_term("LineNo")),
                    []( deque<Thing*> ts ) {
                        Tuple *t = new Tuple();
                        t->append(ts[0]);
                        t->append(ts[1]);
                        return t;
                    }));
            

            return parser;
        }

        bool parse_test_star() {
            parse::Parser grammar;
            grammar.rule( "<start>", apply(star(seq(lit("A"),lit("B"))), [](deque<Thing*> ts){
                Tuple *t  = new Tuple();
                for(size_t i=0; i<ts.size(); ++i) {
                    t->append( ts[i]->clone() );
                }
                return t;
            }));
            stringstream test0;
            test0 << "A B A B";

            grammar.q_stream(test0);
            Thing * result = grammar.parse_thing("<start>");
            std::cout << "Result: ";
            result->serialize_to(std::cout);
            std::cout << "\n";
            return true;
        }

        bool parse_seq() {
            // test only sequences
            parse::Parser grammar;
            grammar.rule(
                "<start>",apply(seq(seq(lit("a"),lit("b")),lit("c")),
                []( deque<Thing*> ts ) {
                    rhizome::types::String *s = new rhizome::types::String();
                    for( size_t i=0; i<ts.size(); ++i) {
                        stringstream ss;
                        ts[i]->serialize_to(ss);
                        s->append( ss.str() );
                    }
                    return s;
                }
            ));
            stringstream test0;
            test0 << "a b c";

            grammar.q_stream(test0);
            Thing * result = grammar.parse_thing( "<start>");

            std::cout << "Result: ";
            result->serialize_to(std::cout);
            std::cout << '\n';
            delete result;
            return true;
        }

        bool parse_literal() {
            parse::Parser grammar;
            grammar.rule("Start",apply(lit("START"),[](deque<Thing*>ts){
                rhizome::types::Tuple *t = new rhizome::types::Tuple();
                for(size_t i=0; i<ts.size();++i) {
                    t->append(ts[i]);
                }
                return t;
            }));
            std::cout << "Testing literal match:\n";
            std::cout << "======================\n";
            stringstream test0;
            test0 << "START";
            grammar.q_stream(test0);
            
            Tuple *vs = (Tuple*)grammar.parse_thing("Start");
            
            bool pass = (vs->size()==1);
            for(size_t i=0; i<vs->size(); ++i) {
                vs->at(i)->serialize_to(std::cout);
                std::cout <<  "\n";
            }
            return pass;
        }

        bool parse_test_match_type() {
            parse::Parser grammar;
            grammar.rule("Start",
                apply(plus(match_type("Integer")), [](deque<Thing*> ts){
                Tuple *t = new Tuple();
                for(size_t i=0; i<ts.size(); ++i) {
                    t->append(ts[i]);
                }
                return t;
            }));

            bool pass(true);
            auto debug_print = [&pass]( string const &vname, Thing *t )  {
                std::cout << vname << " = ";
                t->serialize_to( std::cout);
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
            grammar.rule("Start",apply(star(lit("A")), [](deque<Thing*> ts){
                Tuple *t = new Tuple();
                for(size_t i=0; i<ts.size(); ++i) {
                    t->append(ts[i]);
                    std::cout << i << " = ";
                    ts[i]->serialize_to(std::cout);
                    std::cout << "\n";
                }
                return t;
            }));

            bool pass(true);
            auto debug_print = [&pass]( string const &vname, Thing *t )  {
                std::cout << vname << " = ";
                t->serialize_to( std::cout);
                std::cout << "( status = " << (pass?"passing":"failing") << " )";
                std::cout << "\n";
            };

            
            stringstream example;
            example << "A A A A A";
            grammar.q_stream(example);
            Tuple *vs = (Tuple*)grammar.parse_thing("Start");    
            pass &= (vs->size()==5);
            debug_print("vs", vs );

            stringstream example2;
            example2 << "A A";
            grammar.q_stream(example2);
            Tuple *vs_also = (Tuple*)grammar.parse_thing("Start");
            pass &= (vs_also->size()==2);
            debug_print("vs", vs_also );
            delete vs;
            delete vs_also;
            return pass;
        }

        bool parse_test_list() {
            parse::Parser grammar;
            grammar.rule( "Start",
                apply(seq(match_type("Integer"), plus(seq(lit(","),match_type("Integer")))),
                []( deque<Thing*> ts ){
                    rhizome::types::Tuple *tuple = new rhizome::types::Tuple();
                    for( size_t i=0; i<ts.size(); ++i) {
                        stringstream ss;
                        ts[i]->serialize_to(ss);
                        std::cout << i << " = ";
                        ts[i]->serialize_to(std::cout);
                        std::cout << "\n";
                        if( ts[i]->rhizome_type()=="Integer") {
                            tuple->append( new rhizome::types::Integer(ss.str()));
                        }
                    }
                    return tuple;
                }
            ));
            std::cout << "Looking up start rule...\n";
            Thing * thing = dynamic_cast<Thing*>(grammar.lookup("Start"));
            if( thing ) {
                std::cout << "Grammar:\nStart -> ";
                thing->serialize_to(std::cout);
                std::cout << "\n";
            }

            
            stringstream test0;
            test0 << "1,2,3,4,5,6";
            grammar.q_stream(test0);
            
            rhizome::types::Tuple *vs = (rhizome::types::Tuple*)grammar.parse_thing("Start");
            
            bool pass = (vs->size()==6);
            vs->serialize_to(std::cout);
            std::cout << "\n";
            
            return pass;
        }

        void parse_demo() {
            typedef function< bool() > ParseTest;
            vector<ParseTest> tests({
                parse_literal,
                parse_test_literal_star,
                parse_test_match_type,
                parse_seq,
                parse_test_star,
                parse_test_list
            });

            for( auto i=tests.begin(); i!=tests.end();i++) {
                std::cout << "Test: \n";
                std::cout << "======\n";
                if( i->operator()() ) {
                    std::cout << "Success!\n";
                } else {
                    std::cout << "Failure!\n";
                }
                std::cout << "\n\n";
            }

            

        }
    }
}