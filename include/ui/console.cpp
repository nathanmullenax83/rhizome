#include "console.hpp"

namespace rhizome {
    namespace ui {
        Console::Console(std::ostream &console): console(console) {

        }

        void
        Console::clear() {
            // Esc[2J
            console << "\033[2J\033[H";
        }

        void
        Console::locate(int x, int y) {
            // Esc[Line;ColumnH
            // Esc[Line;Columnf
            console << "\033[" << y << ";" << x << "H";
        }

        void
        Console::cursor_up( size_t n ) {
            // Esc[ValueA
            console << "\033[" << n << "A";
        }

        void
        Console::cursor_down( size_t n ) {
            // Esc[ValueB
            console << "\033[" << n << "B";
        }

        void
        Console::set_mode( int mode ) {
            // Esc[=Valueh
            console << "\033[=" << mode << "h";
        }

        void 
        Console::save_cursor_position() {
            // Esc[s
            console << "\033[s";
        }

        void
        Console::restore_cursor_position() {
            // Esc[u
            console << "\033[u";
        }

        void
        Console::erase_line() {
            // Esc[K
            console << "\033[K";
        }

        void 
        Console::shift_out() {
            console << "\016";
        }

        void
        Console::shift_in() {
            console << "\017";
        }

        void 
        Console::fill_region( ScreenRegion const &rect, string const &fill ) {
            
            stringstream line_ss;
            for(size_t i=0; i<rect.width; ++i) {
                line_ss << fill;
            }
            string line = line_ss.str();
            for(size_t i=0; i<rect.height; ++i) {
                locate( rect.x0,rect.y0+i );
                (*this) << line;
            }

        }

        Console & 
        Console::operator<< ( string const &s ) {
            console << s;
            return *this;
        }

        Console &
        Console::operator<< (int n) {
            console << n;
            return *this;
        }
    }
}