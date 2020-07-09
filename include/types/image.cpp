#include "image.hpp"

namespace rhizome {
    namespace types {
        void image_demo() {
            
            std::cout << "Image Demo." << std::endl;
            Image x;
            x.set_size(500,500);
            x.checker_board( 16,16, Color(1,1,1,1), Color(1,0,0,1));
            x.save_png("test.png");

            Image y; 
            y.freeimage_load("include/image/back.png");
            y.freeimage_save("withfreeimage.png");
            
            
        }

        Image::~Image() {

        }

        void Image::set_size( size_t width, size_t height ) {
            this->width = width;
            this->height = height;
            while( pixels.size() < width*height ) {
                pixels.push_back( Color() );
            }
        }

        void Image::open_png_alpha( string const &path ) {
            png::image< png::rgba_pixel > image( path.c_str() );
            size_t height = image.get_height();
            size_t width = image.get_width();
            set_size(width,height);
            for(size_t y=0; y<height; ++y) {
                for(size_t x=0; x<width; ++x) {
                    png::rgba_pixel p = image[y][x];
                    pixels[x+y*width] = Color(p.red/256.0,p.green/256.0,p.blue/256.0,p.alpha/256.0 );
                }
            }
        }

        void Image::open_png( string const &path ) {
            png::image< png::rgb_pixel > image(path.c_str());
            size_t height = image.get_height();
            size_t width = image.get_width();
            set_size(width,height);
            for(size_t y=0; y<height; ++y) {
                for(size_t x=0; x<width; ++x) {
                    png::rgb_pixel p = image[y][x];
                    Color &d = pixels[x+y*width];
                    d.r = rhizome::types::clamp(p.red/256.0);
                    d.g = rhizome::types::clamp(p.green/256.0);
                    d.b = rhizome::types::clamp(p.blue/256.0);
                    d.a = 1.0;
                }
            }
        }

        void Image::save_png_alpha( string const &path ) {
            png::image< png::rgba_pixel > im(height,width);
            for(size_t y=0; y<height; ++y) {
                for(size_t x=0; x<width; ++x) {
                    png::rgba_pixel p;
                    p.red = std::floor(pixels[x+y*width].r*256.0);
                    p.green = std::floor(pixels[x+y*width].g*256.0);
                    p.blue = std::floor(pixels[x+y*width].b*256.0);
                    p.alpha = std::floor(pixels[x+y*width].a*256.0);
                    im[y][x] = p;
                }
            }
            im.write(path.c_str());
        }

        void Image::save_png( string const &path ) {
            png::image< png::rgb_pixel > im( height, width );
            for(size_t y=0; y<height; ++y) {
                for(size_t x=0; x<width; ++x) {
                    png::rgb_pixel p;
                    Color c = pixels[x+y*width];
                    p.red = std::floor(c.r*256.0);
                    p.green = std::floor(c.g*256.0);
                    p.blue = std::floor(c.b*256.0);
                    im[y][x] = p;
                }
            }
            im.write( path.c_str() );
            
        }

        void Image::pset( size_t x, size_t y, Color const &c ) {
            pixels[x + y*width] = c;
        }

        rhizome::types::Color
        Image::pget( size_t x, size_t y ) {
            return pixels[x+y*width];
        }

        void Image::checker_board( size_t h, size_t w, Color const &a, Color const &b ) {
            for(size_t y=0; y<height; ++y) {
                for(size_t x=0; x<width; ++x) {
                    pset(x,y,(y/h + x/w)%2==0 ? a : b );
                }
            }
        }

        rhizome::types::Color
        from_quad( RGBQUAD const &q ) {
            rhizome::types::Color c;
            c.r = q.rgbRed/255.0;
            c.g = q.rgbGreen/255.0;
            c.b = q.rgbBlue/255.0;
            return c;
        }

        RGBQUAD from_color( rhizome::types::Color const &c) {
            RGBQUAD q;
            q.rgbRed = (unsigned char) std::floor( 255.0*c.r );
            q.rgbGreen = (unsigned char) std::floor( 255.0*c.g );
            q.rgbBlue = (unsigned char) std::floor( 255.0*c.b );
            return q;
        }

        bool 
        Image::freeimage_load( string const &path ) {
            
            fipImage im;
            if(im.load( path.c_str() )) {
                set_size(im.getWidth(), im.getHeight());
                for(size_t y=0; y<im.getHeight(); ++y) {
                    for(size_t x=0; x<im.getWidth(); ++x) {
                        RGBQUAD color;
                        im.getPixelColor(x,y,&color);
                        if( x==y && x==250 ) {
                            std::cout << ((int)color.rgbGreen) <<"\n";
                        }
                        pset( x,y, from_quad(color));
                    }
                }
                return true;
            } else {
                throw runtime_error("freeimage_load: could not load image");
            }
        }

        void
        Image::freeimage_save( string const &path ) {
            fipImage im;
            im.setSize(FREE_IMAGE_TYPE::FIT_BITMAP,width,height,8);
            for(size_t y=0; y<height; ++y) {
                for(size_t x=0; x<width; ++x) {
                    RGBQUAD q;
                    q = from_color(pget(x,y));
                    if( x==y && x==250 ) {
                        std::cout << ((int)q.rgbGreen)<<"\n";
                    }
                    im.setPixelColor(x,y,&q);
                }
            }
            if( !FreeImage_Save(FIF_PNG,im, path.c_str()) ) {
                throw runtime_error("Couldn't save image.");
            } 
            
        }

        void
        Image::serialize_to( size_t level, ostream &out ) const {
            (void) level;
            out << "Image";
            throw runtime_error("Not implemented.");
        }

        Thing *
        Image::clone() const {
            Image *copy = new Image(*this);
            return copy;
        }

        string
        Image::rhizome_type() const {
            return "Image";
        }

        bool
        Image::has_interface(string const &w) {
            return (w==rhizome_type()||w=="Thing");
        }

        Thing *
        Image::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)method;(void)arg;(void)context;
            throw runtime_error("Nothing to invoke.");
        }
    }
}
