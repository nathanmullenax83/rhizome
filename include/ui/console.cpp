#include "console.hpp"

namespace rhizome {
    namespace ui {
        Console::Console(std::ostream &console, size_t x, size_t y, size_t width, size_t height)
        : console(console), x(x), y(y), width(width), height(height)  {
            struct termios current;
            tcgetattr(0,&current);
            termios_configs.push(current);
            tcsetattr(0,TCSANOW,&termios_configs.top());
        }

        void
        Console::clear(char fill) {
            // Esc[2J
            // 
            string blankrow(width,fill);
            locate(0,0);
            console << RESET_COLOR;
            save_cursor_position();
            for(size_t i=0; i<height;++i) {
                locate(0,i);
                (*this) << blankrow;
            }
            restore_cursor_position();
        }

        void
        Console::clear_screen() {
            console << "\033[2J\033[H";
        }

        void
        Console::locate(size_t x, size_t y) {
            assert( x < width );
            assert( y < height );
            // Esc[Line;ColumnH
            // Esc[Line;Columnf
            console << "\033[" << (this->y+y) << ";" << (this->x + x) << "H";
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


        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t> > & 
        Console::get_converter() {
            return converter;
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

        Console &
        Console::operator<< (Thing *t) {
            t->serialize_to(console);
            return *this;
        }

        void Console::push_termios(function< void(struct termios &) > create_top) {
            struct termios current;
            tcgetattr(0, &current);
            // allocate it on the state.
            termios_configs.push(current);
            // run the custom function
            create_top( termios_configs.top());
            tcsetattr(0,TCSANOW, &termios_configs.top());
        }

        void Console::pop_termios() {
            if( termios_configs.size() > 1 ) {
                termios_configs.pop();
                tcsetattr( 0, TCSANOW, &termios_configs.top());
            } else {
                throw runtime_error("Must be one termios state at bottom.");
            }
        }

        void Console::putch( wchar_t c ) {
            string utf8 = converter.to_bytes( {c});
            console << utf8;
        }

        Console & Console::h1(string const &s) {
            std::wstring expanded = converter.from_bytes(s);
            int w = 80;
            int start = w/2 - expanded.length()/2;
            std::string spacer(start-1,' ');
            std::wstring underbar(expanded.length(),L'―');
            console << "\n";
            console << spacer << FG_WHITE_ON << " " << s << "\n";
            console << RESET_COLOR;
            console << spacer << converter.to_bytes(underbar) << "\n\n";
            return *this;
        }

        unsigned long long Console::termios_getch(bool echo) {
            push_termios( [&echo]( termios &t ){
                t.c_lflag &= ~ICANON;
                if(echo) {
                    t.c_lflag |= ECHO;
                } else {
                    t.c_lflag &= ~ECHO;
                }
            });
            unsigned long long int c = getchar();
            pop_termios();
            return c;
        }

        string console_true_color( unsigned char r, unsigned char g, unsigned char b) {
            stringstream c;
            c << "\x1b[38" <<";" <<r << ";"<<g <<";" << b << "m";
            return c.str();
        }
    }
}