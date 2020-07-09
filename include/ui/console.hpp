#ifndef RHIZOME_UI_CONSOLE_HPP
#define RHIZOME_UI_CONSOLE_HPP

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <functional>
#include <codecvt>
#include <locale>
#include <cwchar>
#include <cassert>

#include <termios.h>
#include <termcap.h>

#include "screen_region.hpp"

#include "core/thing.hpp"

using std::ostream;
using std::string;
using std::stringstream;
using std::stack;
using std::function;
using std::runtime_error;

using rhizome::core::Thing;

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

        string console_true_color( unsigned char r, unsigned char g, unsigned char b );
        static const string TRUE_COLOR_OFF("\x1b[0m");

        class Console {
        private:
            std::ostream &console;
            size_t x;
            size_t y;
            size_t width;
            size_t height;
            

            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            // To implement 'getch' style input we need:
            stack< struct termios > termios_configs;
            /// Push current termios state.
            void push_termios(function< void(struct termios &) > create_top );
            /// pop and enable termios state
            void pop_termios();
        public:
            Console(std::ostream &console, size_t x=0, size_t y=0, size_t width=40, size_t height=30);

            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t> > & get_converter();

            void clear(char fill=' ');
            void clear_screen();
            void locate( size_t x, size_t y );
            void cursor_up( size_t n=1);
            void cursor_down( size_t n=1);
            void set_mode( int mode );
            void putch( wchar_t c );

            void save_cursor_position();
            void restore_cursor_position();
            /// Erases from the current cursor position to the end of the line.
            void erase_line();
            void shift_out(); // alternate character set?
            void shift_in();  // back to normal, either way.
            unsigned long long termios_getch(bool echo); 

            /// Level 1 heading
            Console & h1(string const &s);
            /// A paragraph
            Console & para( string const &p );

            
            
            void fill_region( ScreenRegion const &rect, string const &fill );

            Console & operator << ( string const &s );
            
            
            Console & operator << ( int n );

            Console & operator << (Thing *t);

            string get_line( string const &prompt );
        };
    }
}

#endif
