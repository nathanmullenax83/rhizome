#include "menu.hpp"
#include "console.hpp"

namespace rhizome {
    namespace ui {

        void
        Menu::display(Console &cons) const {
            bool can_dazzle = items.size() > 2 && (items.size()%2==1);
            for(size_t i=0; i<items.size(); ++i) {
                if( can_dazzle ) {
                    if( i==0 ) {
                        cons << lcb_upper_hook;
                    } else if (i==items.size()/2) {
                        cons << lcb_middle_piece;
                    } else if (i==items.size()-1) {
                        std::cout << lcb_lower_hook;
                    } else {
                        std::cout <<  cb_extender;
                    }
                    std::cout << " ";
                }
                std::cout << i << ": " << items[i].first << std::endl;
            }
        }

        void
        Menu::choose(Console &cons) {
            cons.clear();
            display(cons);
            size_t choice(0);
            cons << "Choose [0 - " << (int)((items.size()-1)) << "]: ";
            while( !(std::cin>>choice)) {
                cons << "Please choose [0 - " << (int)((items.size()-1)) << "]: ";
                std::cin.clear();
                std::cin.ignore(INT32_MAX,'\n');
            }
            cons.clear();
            select(choice);
        }

        void menu_demo() {

        }
    }
}