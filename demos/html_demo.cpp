#include "html_demo.hpp"
#include <iostream>


using std::cout;
namespace rh =  rhizome::html;

using rhizome::ui::Console;

namespace rhizome {
    namespace demo {
        void html_demo() {
            Console console(std::cout);
            console.h1("Generating HTML document.");
            
            rh::HTML doc("HTML Generation demo.");
            doc.body.h1("Rhizome is a Couple of Things");
            //doc.body.p("test");
            doc.body.ul([]( rh::UL &ul ) {
                ul.li("A parser embedding tool.");
                ul.li("An offline data storage format.");
                ul.li("A server?");
            });
            
            
            
            doc.write_to(cout);
            cout << "\n\n";
            doc.serialize_to(0,cout);
            console.termios_getch(false);
            console.termios_getch(false);
        }
    }
}