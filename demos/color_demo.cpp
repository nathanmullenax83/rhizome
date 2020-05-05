#include "color_demo.hpp"

namespace rhizome {
    namespace demo {
        void color_demo() {
            static rhizome::log::Log log("demos",false);
            log.info("Launched color demo.");
            std::cout << " Color Demo" << std::endl;
            std::cout << "============" << std::endl;
            vector<Color> cs;
            std::cout << "Hex\t\tIntensity\t\tDec\t\tHue" << std::endl;
            for(size_t i=0; i<10; ++i) {
                Color c;
                c.randomize();
                cs.push_back(c);
                std::cout << c.hex() << "\t\t" << c.intensity() << "\t\t" << c <<
                    "\t\t" << c.hue() << "\t\t" << std::endl;
            }

            // kind random reflection test: querying for an interface
            Color c;
            c.has_interface("Color");
            c.has_interface("Thing");
            

            log.info("Color demo ended normally.");
        }
    }
}