#ifndef RHIZOME_IMAGE_HPP
#define RHIZOME_IMAGE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <png++/png.hpp>
#include <FreeImage.h>
#include <FreeImagePlus.h>
#include "core/thing.hpp"
#include "color.hpp"


using std::string;
using std::vector;
using rhizome::core::Thing;
using rhizome::types::Color;


namespace rhizome {
    namespace types {
        void image_demo();

        class Image: public Thing {
        private:
            size_t width;
            size_t height;
            vector<Color> pixels;
        public:
            virtual ~Image();

            void pset( size_t x, size_t y, Color const &c );
            Color pget( size_t x, size_t y );
            void set_size( size_t width, size_t height );
            void open_png_alpha( string const &path );
            void save_png_alpha( string const &path );
            void open_png( string const &path );
            void save_png( string const &path );

            bool freeimage_load( string const &path );
            void freeimage_save( string const &path );

            void checker_board( size_t h, size_t w, Color const &a, Color const &b );

            // Thing interface
            virtual void serialize_to( ostream &out ) const override;
            virtual string rhizome_type() const override;

            virtual Thing * clone() const override;
            virtual bool has_interface(string const &name) override;
            virtual Thing * invoke(Thing *context, string const &method, Thing *arg ) override;
        };
    }
}

#endif
