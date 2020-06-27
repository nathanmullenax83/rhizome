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
            a->invoke("=",b);
            outvar(console,"A",a); // false
            outvar(console,"B",b); // false
                                   // c is true
            substep( console, "A ⊕= C");
            a->invoke("⊕=",c);
            outvar(console,"A",a); // true
                                   // b is false
            outvar(console,"C",c); // true
            substep(console, "A |= B");
            a->invoke("|=",b);
            outvar(console,"A",a); // true

            delete a;
            delete b;
            delete c;
            return passed;
        }

        void types_demo() {
            Console console(std::cout);
            bool_test(console);

            cout << "Creating an integer: " << endl;
            Integer j("2347");
            cout << j << endl;
            cout << "Prime? " << j.is_prime() << endl;

            cout << "Creating a string: " << endl;
            String s("Hello world!");
            cout << s << endl;

            cout << "Creating a float: " << Float(0.4) << endl;

            cout << "Creating some fractions: " << endl;
            Fraction q1(64,12);
            Fraction q2(164,12);
            Fraction q3(87,10);
            Fraction q4(64,2);
            Fraction q5(123,5);

            cout << q1 << endl;
            cout << q2 << endl;
            cout << q3 << endl;
            cout << q4 << endl;
            cout << q5 << endl;
            
            console.termios_getch(false);
            console.termios_getch(false);
        }
    }
}