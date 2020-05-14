#include "qbasic.hpp"

namespace rhizome {
    namespace demos {
        IParser *
        QBasic::create_parser() {
            Parser *parser = new Parser();

            parser->rule("Program", plus(non_term("Line")), 
            [](deque<Thing*> ts) {
                Enumeration * lines = new Enumeration();
                for(size_t i=0; i<ts.size(); ++i) {
                    Tuple *line = (Tuple*)ts[i];
                    Integer *n = (Integer*)line->at(0);
                    Thing *statement = line->at(1);
                    lines->set( *n, statement );
                }
                return lines;
            });

            parser->rule("Line", 
                seq(match_type("Integer"),non_term("Statement")),
            [](deque<Thing*> ts) {
                Tuple * line = new Tuple();
                line->append( ts[0]);
                line->append( ts[1]);
                return (Thing*)line;
            });

            parser->rule( "Statement", options({
                non_term("PrintStatement"),
                non_term("GotoStatement"),
                non_term("ForBlock"),
                non_term("EndStatement")
            }), 
            [](deque<Thing*> ts){
                Tuple *statements;
                for(size_t i=0; i<ts.size(); ++i) {
                    statements->append(ts[i]);
                }
                return (Thing*)statements;
            });

            parser->rule("GotoStatement",seq(lit("GOTO"), match_type("Integer")),
            [](deque<Thing*> ts) {
                Tuple *gt = new Tuple();
                gt->append( ts[0]);
                gt->append( ts[1]);
                return gt;
            });

            return parser;
        }
    }
}