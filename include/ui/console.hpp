#ifndef RHIZOME_UI_CONSOLE_HPP
#define RHIZOME_UI_CONSOLE_HPP

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <termios.h>
#include <termcap.h>

#include "screen_region.hpp"

using std::ostream;
using std::string;
using std::stringstream;



namespace rhizome {
    namespace ui {
        // ansii stuff
        static const string FG_RED_ON("\033[1;31m");
        static const string FG_GREEN_ON("\033[1;32m");
        static const string FG_YELLOW_ON("\033[1;33m");
        static const string FG_CYAN_ON("\033[1;36m");
        static const string FG_BLACK_ON("\033[1;30m");
        static const string FG_BLUE_ON("\033[1;34m");
        static const string FG_MAGENTA_ON("\033[1;35m");
        static const string FG_WHITE_ON("\033[1;37m");

        static const string BG_BLACK_ON("\033[1;40m");
        static const string BG_RED_ON("\033[1;41m");
        static const string BG_GREEN_ON("\033[1;42m");
        static const string BG_YELLOW_ON("\033[1;43m");
        static const string BG_BLUE_ON("\033[1;44m");
        static const string BG_MAGENTA_ON("\033[1;45m");
        static const string BG_CYAN_ON("\033[1;46m");
        static const string BG_WHITE_ON("\033[1;47m");

        static const string RESET_COLOR("\033[0m");
        
        // unicode stuff.
        static const string Delta =            "\u0394";
        static const string delta =            "\u03B4";
        static const string telephone =        "\u260E";
        static const string integral =         "\u222B";
        static const string therefore =        "\u2234";
        static const string because =          "\u2235";

        static const string  cb_extender     = "\u23AA";
        static const string lcb_upper_hook   = "\u23A7";
        static const string lcb_middle_piece = "\u23A8";
        static const string lcb_lower_hook   = "\u23A9";

        static const string rcb_upper_hook   = "\u23AB";
        static const string rcb_middle_piece = "\u23AC";
        static const string rcb_lower_hook   = "\u23AD";

        static const string recycle          = "\u267b";

        static const string zodiak_capricorn = "\u2651";
        static const string hammer_and_sickle= "\u262d";
        static const string peace            = "\u262e";
        static const string skull_and_bones  = "\u2620";
        static const string warning          = "\u26A0";

        static const string boldserif_A      = "\U0001D468";
        

        static const string die[] = {
            "\u2680",
            "\u2681",
            "\u2682",
            "\u2683",
            "\u2684",
            "\u2685"
        };

        class Console {
        private:
            size_t x;
            size_t y;

            std::ostream &console;
        public:
            Console(std::ostream &console);

            void clear();
            void locate( int x, int y );
            void cursor_up( size_t n=1);
            void cursor_down( size_t n=1);
            void set_mode( int mode );
            void save_cursor_position();
            void restore_cursor_position();
            /// Erases from the current cursor position to the end of the line.
            void erase_line();
            void shift_out(); // alternate character set?
            void shift_in();  // back to normal, either way.
            
            void fill_region( ScreenRegion const &rect, string const &fill );

            Console & operator << ( string const &s );
            
            
            Console & operator << ( int n );
        };
    }
}

#endif
