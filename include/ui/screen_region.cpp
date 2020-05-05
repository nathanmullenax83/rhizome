#include "screen_region.hpp"

namespace rhizome {
    namespace ui {
        ScreenRegion::ScreenRegion(): x0(1), y0(1), width(80), height(25) {}

        ScreenRegion::ScreenRegion( size_t x0, size_t y0, size_t width, size_t height )
        : x0(x0), y0(y0), width(width), height(height) {}

        void ScreenRegion::horizontal_split( ScreenRegion &left, ScreenRegion &right ) const {
            left.height = right.height = height;
            left.x0 = x0;
            left.y0 = y0;
            right.y0 = y0;
            right.x0 = x0 + width/2;
            left.width = width/2;
            right.width = width - left.width;
        }

        void ScreenRegion::vertical_split( ScreenRegion &top, ScreenRegion &bottom ) const {
            top.height = height/2;
            bottom.height = height-top.height;
            top.y0 = y0;
            bottom.y0 = y0 + top.height;
            top.x0 = x0;
            bottom.x0 = x0;
            top.width = width;
            bottom.width = width;
        }

        ScreenRegion ScreenRegion::shrink( size_t hshrink, size_t vshrink ) const {
            ScreenRegion rect;
            rect.x0 = x0 + hshrink;
            rect.y0 = y0 + vshrink;
            rect.height = height - 2*vshrink;
            rect.width = width - 2*hshrink;
            return rect;
        }
    }
}