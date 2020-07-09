#include "types_demo.hpp"

using rhizome::ui::Console;
using rhizome::types::Bool;

namespace rhizome {
    namespace demo {
        Console & outvar( Console &c, string const &name, Thing *t ) {
            c << "    " << name << " = " << t << "\n";
            return c;
        }

        Console & step( Console &c, string const &desc ) {
            c << "\n- " << rhizome::ui::FG_WHITE_ON;
            c << desc << "\n  ";
            for(size_t i=0; i<desc.size(); ++i) {
                c << "―";
            }
            c << rhizome::ui::RESET_COLOR;
            
            c << "\n";
            return c;
        }
        
        Console & substep( Console &c, string const &desc ) {
            c << "  • " << rhizome::ui::FG_YELLOW_ON;
            c << desc;
            c << rhizome::ui::RESET_COLOR;
            c << "\n";
            return c;
        }

        bool bool_test( Console &console ) {
            bool passed = true;

            console.clear();
            step( console, "Creating boolean variables A, B, and C" );
            Bool *a = new Bool(true);
            Bool *b = new Bool(false);
            Bool *c = new Bool(true);
            
            outvar(console, "A", a);
            outvar(console, "B", b);
            outvar(console, "C", c);

            step( console, "Testing invoke methods." );
            substep( console, "A = B");
            a->invoke(NULL,"=",b);
            outvar(console,"A",a); // false
            outvar(console,"B",b); // false
                                   // c is true
            substep( console, "A ⊕= C");
            a->invoke(NULL,"⊕=",c);
            outvar(console,"A",a); // true
                                   // b is false
            outvar(console,"C",c); // true
            substep(console, "A |= B");
            a->invoke(NULL,"|=",b);
            outvar(console,"A",a); // true

            delete a;
            delete b;
            delete c;
            return passed;
        }

        void types_demo() {
            Console console(std::cout);
            bool_test(console);
            step(console,"Creating an integer.");            
            Integer j("2347");
            outvar( console, "j",&j);
            substep(console, "Check if integer is prime.");

            Thing *result = j.invoke(NULL,"ϵℙ",NULL);
            bool n_result = rhizome::system_bool(result);
            delete result;

            cout << (n_result?"    j is prime":"    j is not prime") << endl;

            step(console, "Creating a string: ");
            String s("Hello world!");
            outvar(console,"s",&s);
            
            step(console, "Creating a float: ");
            Float f(0.4);
            outvar(console,"f",&f);
            step(console,"Creating and reducing some fractions.");
            
            Fraction q1(64,12);
            Fraction q2(164,12);
            Fraction q3(87,10);
            Fraction q4(64,2);
            Fraction q5(123,5);

            outvar(console,"q1",&q1);
            outvar(console,"q2",&q2);
            outvar(console,"q3",&q3);
            outvar(console,"q4",&q4);
            outvar(console,"q5",&q5);
            
            console.termios_getch(false);
            console.termios_getch(false);
        }
    }
}