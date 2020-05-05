#include "html_demo.hpp"
#include <iostream>


using std::cout;
namespace rh =  rhizome::html;

namespace rhizome {
    namespace demo {
        void html_demo() {
            
            rh::HTML doc("HTML Generation demo.");
            doc.body.h1("Article Title");
            //doc.body.p("test");
            doc.body.ul([]( rh::UL &ul ) {
                ul.li("one");
                ul.li("two");
                ul.li("three");
            });
            
            
            doc.write_to(cout);
            cout << "\n\n";
            doc.serialize_to(cout);

        }
    }
}