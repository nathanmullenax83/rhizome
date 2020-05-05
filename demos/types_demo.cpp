#include "types_demo.hpp"

namespace rhizome {
    namespace demo {
        void types_demo() {
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
            
        }
    }
}