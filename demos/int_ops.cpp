#include "rhizome.hpp"

using rhizome::alphabet::Classifier;
using rhizome::types::Operator;
using rhizome::types::Integer;
using rhizome::ui::Console;
using rhizome::lex::Lexer;

namespace rhizome {
    namespace demo {
        
        void summarize_operator( Operator *p ) {
            std::cout << "Operator Definition:\n\t";
            p->serialize_to(1,std::cout);
            std::cout << "\n";
        }

        void int_ops() {
            Console console(std::cout);
            // create a blank-slate lexer and parser combo.
            Parser *p = new Parser(new Lexer());

            // define a few operators
            Operator *bang = new Operator(L"!", [](){
                return new Integer(1);
            });

            Operator *plus = new Operator(L"+", [](Thing *a, Thing *b){
                return (a->clone())->invoke(NULL,"+",b);
            },rhizome::types::LEFT_TO_RIGHT);

            Operator *times = new Operator(L"*",[](Thing *a, Thing *b){
                return (a->clone())->invoke(NULL,"-",b);
            },rhizome::types::LEFT_TO_RIGHT);


            summarize_operator(bang);
            summarize_operator(plus);
            summarize_operator(times);

            console.termios_getch(false);
            console.termios_getch(false);
            delete bang;
            delete plus;
            delete p;
            
        }
    }
}