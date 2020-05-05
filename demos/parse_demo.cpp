#include "parse_demo.hpp"

using rhizome::types::Tuple;
using rhizome::types::Integer;
using rhizome::types::String;
using rhizome::types::Table;

namespace rhizome {
    namespace demo {
//         1 REM                          MISSILE
// 2 REM                    By Kenneth Green
// 3 REM             Go click on Run above and then start.
// 4 REM
// 5 REM
// 6 REM
// 7 REM
// 8 REM --------------------Program Below--------------------------------------
// 9 x1 = 0: x2 = 0
// 10 CLS : SCREEN 0
// 15 tr = 1
// 20 PRINT "                   MISSILE"
// 25 PRINT "                   -------"
// 30 PRINT : PRINT : PRINT : PRINT "By Kenneth Green"
// 35 PRINT : PRINT : PRINT "This game lets you type a one": PRINT "number coordinate to lock on and destroy"
// 36 PRINT "your enemy."
// 38 PRINT "You can have as many tries as you want,": PRINT "it says your tries after you win."
// 39 PRINT "To end the game, type 0 as your": PRINT "coordinate.": PRINT "The enemy is in a different": PRINT "spot every time!"
// 40 INPUT "Press <Enter> to start this game."; go$
// 45 RANDOMIZE TIMER
// 50 x1 = RND(1) * 10
// 55 x2 = RND(1) * 10
// 60 x3 = x2 * x1 + 130
// 70 x4 = RND * 200
// 80 IF x4 < 120 THEN 70
// 99 SCREEN 1
// 100 LINE (100, 185)-(109, 150), , BF: REM ***MOUNTAIN***
// 105 LINE (50, 185)-(60, 170), , B: REM ****YOU****
// 107 LOCATE 5, 5: PRINT "YOU"
// 135 LOCATE 5, 20: PRINT "ENEMY"
// 140 LINE (x3, 180)-(x3 + 5, 185), , B: REM ****ENEMY****
// 142 LINE (x4, 180)-(x4 + 5, 185), , B: REM ***ENEMY 2***
// 143 LINE (0, 185)-(300, 185)
// 145 IF tr = 7 THEN 700
// 150 LOCATE 1, 1: INPUT "Number between 1 and 300, or 0 to end:"; g
// 155 IF g = 0 THEN 520
// 156 FOR tn = 10 TO 46 STEP 2
// 160 LINE (52, 183)-((g / 2) + 55, 80)
// 163 SOUND 100 + tn, 1
// 165 FOR tym = 1 TO 500: NEXT tym
// 166 LINE ((g / 2) + 55, 80)-(g + 3, 185)
// 170 LINE (g + 2, 180)-(g + 3, 184), , BF
// 175 NEXT tn
// 180 IF g = x3 THEN 500
// 190 IF g < x3 + 3 AND g > x3 - 3 THEN 500
// 191 IF g < x4 + 3 AND g > x4 - 3 THEN 500
// 195 IF g > 49 AND g < 56 THEN 600
// 200 LOCATE 2, 1: PRINT "Missed"
// 202 tr = tr + 1
// 205 FOR tm = 1 TO 60000: NEXT tm
// 206 LOCATE 2, 1: PRINT "      "
// 210 SCREEN 2: GOTO 99
// 500 FOR ex = 1 TO 9: CIRCLE (g + 2, 184), ex: SOUND 100, 1: FOR ti = 1 TO 5000: NEXT ti: NEXT ex
// 505 FOR m = 1 TO 95000: NEXT m
// 506 SCREEN 0
// 510 PRINT "YOU WON. You took "; tr;
// 515 IF tr = 1 THEN PRINT "try!"
// 517 IF tr > 1 THEN PRINT "tries."
// 518 IF tr = 1 THEN PRINT "You are ranked General."
// 519 IF tr = 2 THEN PRINT "You are ranked Leutenant Commander."
// 520 IF tr = 3 THEN PRINT "You are ranked First Leutenant."
// 521 IF tr = 4 THEN PRINT "You are ranked Sargent."
// 522 IF tr = 5 THEN PRINT "You are ranked Captain."
// 523 IF tr = 6 THEN PRINT "You are ranked Cadet."
// 539 INPUT "Do you want to play again(Y/N)"; ag$
// 530 IF ag$ = "Y" OR ag$ = "y" OR ag$ = "YES" OR ag$ = "Yes" OR ag$ = "yes" THEN 10
// 550 END
// 600 FOR ep = 1 TO 8: CIRCLE (53, 182), ep: SOUND 100, 1: FOR ty = 1 TO 7000: NEXT ty: NEXT ep
// 605 FOR tym = 1 TO 80000: NEXT tym
// 606 SCREEN 0
// 610 PRINT "You destroyed yourself."
// 620 PRINT : PRINT : PRINT
// 630 INPUT "Again(Y/N)"; an$
// 640 IF an$ = "y" OR an$ = "yes" OR an$ = "YES" OR an$ = "Y" THEN 10
// 650 END
// 700 LINE (x3, 180)-(x3 - 55, 50): LINE (x3 - 55, 50)-(55, 180)
// 710 LINE (x4, 180)-(x4 - 55, 50): LINE (x4 - 55, 50)-(55, 180)
// 720 FOR c3 = 1 TO 25: SOUND c3 + 100, 1
// 730 FOR tm = 1 TO 200: NEXT tm: CIRCLE (55, 180), c3: NEXT c3
// 740 LOCATE 3, 10: PRINT "The enemies have destroyed your base!"
// 750 GOTO 539
        

        parse::Parser * create_BASIC_grammar() {
            
            parse::Parser *parser = new parse::Parser();
                parser->rule( 
                    "Program", plus(non_term("Statement")),
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
                    });
                parser->rule( 
                    "Statement", 
                        seq(non_term("LineNo"),
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
                }
                
            );
            parser->rule(
                    "EndStatement",
                    lit("END"),
                    []( deque<Thing*> ts ) {
                        return ts[0];
                    });
            parser->rule(
                    "ClsStatement",
                    lit("CLS"),
                    []( deque<Thing*> ts ) {
                        return ts[0];
                    });
            parser->rule(
                    "GotoStatement",
                    seq(lit("GOTO"),non_term("LineNo")),
                    []( deque<Thing*> ts ) {
                        Tuple *t = new Tuple();
                        t->append(ts[0]);
                        t->append(ts[1]);
                        return t;
                    });
            

            return parser;
        }

        bool parse_test_star() {
            parse::Parser grammar;
            grammar.rule( "<start>", star(seq(lit("A"),lit("B"))), [](deque<Thing*> ts){
                Tuple *t  = new Tuple();
                for(size_t i=0; i<ts.size(); ++i) {
                    t->append( ts[i]->clone() );
                }
                return t;
            });
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
                "<start>",seq(seq(lit("a"),lit("b")),lit("c")),
                []( deque<Thing*> ts ) {
                    rhizome::types::String *s = new rhizome::types::String();
                    for( size_t i=0; i<ts.size(); ++i) {
                        stringstream ss;
                        ts[i]->serialize_to(ss);
                        s->append( ss.str() );
                    }
                    return s;
                }
            );
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
            grammar.rule("Start",lit("START"),[](deque<Thing*>ts){
                rhizome::types::Tuple *t = new rhizome::types::Tuple();
                for(size_t i=0; i<ts.size();++i) {
                    t->append(ts[i]);
                }
                return t;
            });
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
            grammar.rule("Start",plus(match_type("Integer")), [](deque<Thing*> ts){
                Tuple *t = new Tuple();
                for(size_t i=0; i<ts.size(); ++i) {
                    t->append(ts[i]);
                }
                return t;
            });

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
            grammar.rule("Start",star(lit("A")), [](deque<Thing*> ts){
                Tuple *t = new Tuple();
                for(size_t i=0; i<ts.size(); ++i) {
                    t->append(ts[i]);
                    std::cout << i << " = ";
                    ts[i]->serialize_to(std::cout);
                    std::cout << "\n";
                }
                return t;
            });

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
                seq(match_type("Integer"), plus(seq(lit(","),match_type("Integer")))),
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
            );
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