#include "menu.hpp"
#include "console.hpp"
#include <locale>
#include <codecvt>
#include <string>

using std::wstring;

namespace rhizome {
    namespace ui {
        // @s is a UTF-8 string containing (perhaps) ANSI formatting junk,
        // which shouldn't count toward the length
        size_t bytes_ansi( string const &s ) {
            size_t len(0);
            size_t begin(s.size()); // sentinal
            for(size_t i=0; i<s.size(); ++i) {
                if( s[i]=='\033') {
                    begin = i;
                }
                if( s[i]=='m' && begin < s.size() ) {
                    len += (i-begin)+1;
                    begin = s.size();
                }
            }
            return len;
        }

        size_t length( string const &s ) {
            // OK, so. s is probably UTF-8 encoded.
            // but none of the regular length or size methods report appropriate
            // lengths for strings! 
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            std::wstring ws = converter.from_bytes(s);
            return ws.size() - bytes_ansi(s);
        }

        void
        Menu::display(Console &cons) const {
            //bool can_dazzle = items.size() > 2 && (items.size()%2==1);
            for(size_t i=0; i<items.size(); ++i) {
              //  if( can_dazzle ) {
                string spacer(length(menuprefix),' ');
                    if( i==0 ) {
                        cons << spacer << lcb_upper_hook;
                    } else if (i==items.size()/2) {
                        cons << menuprefix << lcb_middle_piece;
                    } else if (i==items.size()-1) {
                        cons << spacer << lcb_lower_hook;
                    } else {
                        cons << spacer << cb_extender;
                    }
                    std::cout << " ";
                //}
                std::cout << i << ": " << FG_WHITE_ON << items[i].first << RESET_COLOR << std::endl;
            }
        }
        
        void 
        Menu::display_inline(Console &con) const {
            for(size_t i=0; i<items.size(); ++i) {
                con << "  " << i << ": " << items[i].first;
            }
        }

        void
        Menu::choose(Console &cons, bool inlined) {
            if(!inlined) {
                cons.clear_screen();
                display(cons);
            } else {
                display_inline(cons);
            }
            size_t choice(0);
            cons << "\n Choose [0 - " << (int)((items.size()-1)) << "]: ";
            while( !(std::cin>>choice)) {
                cons << "Please choose [0 - " << (int)((items.size()-1)) << "]: ";
                std::cin.clear();
                std::cin.ignore(INT32_MAX,'\n');
            }
            if( !inlined ) {
                cons.clear_screen();
            }
            select(choice);
        }

        

        void menu_demo() {

        }
    }
}