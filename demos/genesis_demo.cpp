#include "genesis_demo.hpp"

namespace rhizome {
    namespace demo {
        void fraction_test(ru::Console &console) {
            
            auto stringify = []( Thing const &t ) {
                stringstream ss;
                t.serialize_to(0,ss);
                return ss.str();
            };
            Fraction f1( rt::Integer(-4),rt::Integer(2));
            Fraction f2(rt::Integer(6),rt::Integer(-2));
            Fraction f3(rt::Integer(-16),rt::Integer(-8));
            console.h1("Creating Test Fractions");
            
            console << "f1 (-4/2)   = " << stringify(f1) << "\n";
            console << "f2 (6/-2)   = " << stringify(f2) << "\n";
            console << "f3 (-16/-8) = " << stringify(f3) << "\n";


            console << "Enter a fraction: ";
            int numerator;
            int denomenator;
            std::cin >> numerator;
            std::cin >> denomenator;
            Fraction f(numerator,denomenator);
            console << "Simplified: " << stringify(f) << "\n\n";
            
            console << "Enter another fraction and we'll add them! ";
            std::cin >> numerator;
            std::cin >> denomenator;
            Fraction g(numerator,denomenator);

            Fraction h = f + g;
            console << "The sum: " << stringify(h) << "\n\n";
            

        }

        void genesis_demo() {
            ru::Console console(std::cout);
            ru::ChessBoard cb(2,2,8,8);
            cb.display(console);
            console.putch('\n');
            
            cb.serialize_to(0,std::cout);
            fraction_test(console);
        }
    }
}