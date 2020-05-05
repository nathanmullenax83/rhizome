#ifndef RHIZOME_UI_SCREEN_REGION
#define RHIZOME_UI_SCREEN_REGION

#include <cstdlib>
#include <algorithm>

namespace rhizome {
    namespace ui {
        class ScreenRegion {
        private:            
            size_t x0;
            size_t y0;
            size_t width;
            size_t height;
        public:
            ScreenRegion();
            ScreenRegion( size_t x0, size_t y0, size_t width, size_t height );

            void horizontal_split( ScreenRegion &left, ScreenRegion &right ) const;
            void vertical_split( ScreenRegion &top, ScreenRegion &bottom ) const;

            ScreenRegion shrink(size_t hshrink, size_t vshrink ) const;

            friend class Console;
        };
    }
}

#endif