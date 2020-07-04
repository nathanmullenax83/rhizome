#ifndef RHIZOME_MENU_HPP
#define RHIZOME_MENU_HPP

#include <vector>
#include <string>
#include <functional>
#include <tuple>
#include <iostream>
#include <ncurses.h>

using std::function;
using std::vector;
using std::string;
using std::pair;

#include "console.hpp"

namespace rhizome {
    namespace ui {

        class UIEvent {
        public: 
            enum Type { KEYDOWN, KEYUP, UP, DOWN, LEFT, RIGHT } type;
        };

        class UIEventDelegate {
        private:
            vector< function<UIEvent(UIEvent)> > listeners;
        public:
            UIEvent operator() ( UIEvent event ) {
                UIEvent e = event;
                for(size_t i=0; i<listeners.size();++i) {
                    e = listeners[i](e);
                }
                return e;
            }

            
            UIEventDelegate & operator+ ( function< UIEvent(UIEvent) > f) {
                listeners.push_back(f);
                return *this;
            }
        };


        /// Menu represents a list of items and corresponding runners.
        class Menu {
        private:
            string menuprefix;
            vector< pair< string, function< void(void) > > > items;
        public:
            Menu() : menuprefix("—rh\033[1;32m🌱\033[0mzome—") {

            }

            void add_item( string const &name, function< void(void) > runner ) {
                items.push_back( pair<string, function<void(void)> >(name,runner) );
            }



            void select( size_t itemNo ) {
                // run the runner
                items[itemNo%items.size()].second();
            }

            void display(Console & console ) const;
            void display_inline(Console &console) const;


            /// Display the menu and prompt for a selection.
            void choose(Console & console, bool inlined=false);
        };

        void menu_demo();

    }
}
#endif
