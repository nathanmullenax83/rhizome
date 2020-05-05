#include "console_demo.hpp"

namespace rhizome {
    namespace demo {
        void ascii_table(ru::Console &console, int offset_y) {
            int pitch = 10;
            for(char i=32; i>=32; ++i) {
                int row = i/pitch + offset_y;
                int col = (i % pitch)*5;
                console.locate(col,row);
                console << i;
            }
        }

        void console_demo() {
            ru::Console console(std::cout);

            ru::ScreenRegion rect;

            
            console.save_cursor_position();
            console.clear();

            console.fill_region( rect, "\u2591");
            ru::ScreenRegion inner_rect = rect.shrink( 2, 1);
            console.fill_region( inner_rect, " ");
            console.locate( 4,4 );
            console << "Unicode delta: " << ru::delta << "\n";
            console << ru::telephone << " call me about unicode.\n";
            console << "I'm a " << ru::zodiak_capricorn << "\n";
            console << ru::recycle << " everything!\n";
            console << ru::boldserif_A << "\n";
            console << ru::hammer_and_sickle << " long live the 5th international!\n";
        }
    }
}