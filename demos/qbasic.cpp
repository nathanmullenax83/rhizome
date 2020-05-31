#include "qbasic.hpp"

using rhizome::lex::Lexer;

namespace rhizome {
    namespace demos {
        

        Lexer * create_qbasic_lexer() {
            Lexer *lexer = new Lexer();
            
            return lexer;
        }

        Parser * create_qbasic_parser() {
            Parser *parser = new Parser(create_qbasic_lexer());
            

            return parser;
        }
    }
}