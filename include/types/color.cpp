#include <cassert>
#include "color.hpp"


using rhizome::core::Dispatcher;
namespace rhizome {
    namespace types {
        

        double clamp(double v) {
            return std::min(std::max(0.0,v),1.0);
        }

        unsigned char expand( double v ) {
            return static_cast<unsigned char> (std::floor(255.0*clamp(v)));

        }

        double random_double() {
            return rand()*1.0/(1.0*INT_MAX);
        }

        char hex_digit( size_t n ) {
            string digs("0123456789abcdef");
            return digs[n%16];
        }


        namespace colors {
            static Dispatcher<Color> dispatcher({
                {
                    "evaluate", [] (Thing *context, Color *that, Thing *arg ) {
                        assert(arg==NULL);
                        return that->evaluate(context);
                    }
                }
            });
        }

        Color::Color()
        : r(0),g(0),b(0),a(1.0) {

        }

        Color::Color( Color const & c): r(c.r), g(c.g), b(c.b), a(c.a) {
            
        }

        Color::Color( double r, double g, double b, double a )
        : r(r),g(g),b(b),a(a) {

        }

        Color::~Color() {
            
        }

        void
        Color::clamp() {
            r = rhizome::types::clamp(r);
            g = rhizome::types::clamp(g);
            b = rhizome::types::clamp(b);
            a = rhizome::types::clamp(a);
        }

        double 
        Color::intensity() {
            return std::sqrt( r*r +g*g + b*b )/std::sqrt(3);
        }

        double
        Color::hue() {
            auto f = [](double v) {
                return 60.0*(v < 0 ? v + 2.0*M_PI : v);
            };
            if( r >= g && r >= b) {
                // If Red is max, then Hue = (G-B)/(max-min)
                // red is max
                return f((g-b)/(r-std::min(g,b)));
            } else if( g >= r && g >= b ) {
                // If Green is max, then Hue = 2.0 + (B-R)/(max-min)
                // green is max
                return f(2.0 + (b-r)/(g-std::min(r,g)));
            } else  {
                // If Blue is max, then Hue = 4.0 + (R-G)/(max-min)
                // blue is max
                return f(4.0 + (r-g)/(b-std::min(r,g)));
            }
            throw runtime_error("Problem with hue computation.");
        }

        double
        Color::max_rgb() {
            return std::max(r,std::max(g,b));
        }

        double
        Color::min_rgb() {
            return std::min(r,std::min(g,b));
        }

        double
        Color::luminosity() {
            return 0.5*(max_rgb()+min_rgb());
        }

        double
        Color::saturation() {
            double L = luminosity();
            if( luminosity() < 1 ) {
                return (max_rgb()-min_rgb())/(1.0 - std::abs(1-2.0*L));
            } else {
                return 0;
            }
        }

        void 
        Color::gray() {
            r = g = b = intensity();
        }

        void
        Color::randomize() {
            r = random_double();
            g = random_double();
            b = random_double();
        }

        string
        Color::hex() {
            string h("      ");
            unsigned char red = expand(r);
            unsigned char green = expand(g);
            unsigned char blue = expand(b);
            h[0] = hex_digit( red/16 );
            h[1] = hex_digit( red%16 );
            h[2] = hex_digit( green/16 );
            h[3] = hex_digit( green%16 );
            h[4] = hex_digit( blue/16 );
            h[5] = hex_digit( blue%16 );
            return h;
        }

        void
        Color::serialize_to( size_t level, ostream &out ) const {
            (void)level;
            // note, the serialize_to method should always be a prototype
            // for an object literal representation on the rhizome parser.
            // This does not preclude other representations. For instance,
            // it is often convenient to specify a color as a hexadecimal
            // web color. These alternative representations are truncated
            // representations of the same. Clearly the below representation
            // can portray all of the web colors, but the inverse is not true.
            // It could be said of the default configuration of the parser:
            //    There is only one internal representation, but there are
            //    uncountably many intermediate representation that can be
            //    supported elsewhere. 
            out << "color(" << r << "," << g << "," << b << ";" << a << ")";
        }

        Thing *
        Color::clone() const {
            Color *c = new Color(r,g,b,a);
            return c;
        }

        string
        Color::rhizome_type() const {
            return "Color";
        }


        bool
        Color::has_interface(string const &w) {
            return (w==rhizome_type()||w=="Thing");
        }


        std::ostream & operator<< ( std::ostream &out, Color const &c ) {
            out << "(" << c.r << "," << c.g << "," << c.b << ";" << c.a << ")";
            return out;
        }

        Thing *
        Color::invoke( Thing *context, string const &method, Thing *arg ) {
            try {
                Thing *r =  colors::dispatcher.at(method)(context,this,arg);
                return r;
            } catch( std::exception *e ) {
                if( colors::dispatcher.count(method)==0) {
                    throw runtime_error(rhizome::core::invoke_method_not_found(method,this,context));
                } else {
                    throw runtime_error(rhizome::core::invoke_error(method,arg,this,context,e));
                }
            }
        }

        Thing *
        Color::evaluate( Thing *context ) const {
            (void)context;
            return clone();
        }

        
    }
}
