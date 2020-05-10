#ifndef RHIZOME_COLOR_HPP
#define RHIZOME_COLOR_HPP

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <vector>
#include <stdexcept>

#include "core/thing.hpp"

using std::string;
using std::vector;
using std::runtime_error;
using std::stringstream;

using rhizome::core::Thing;


namespace rhizome {
    namespace types {
        double clamp( double v );

        /// Take a double in the range [0,1] and turn it into
        /// an unsigned byte.
        unsigned char expand( double v );

        double random_double();
        char hex_digit( size_t n );

        class Color : public Thing {
        public:
            
            double r;
            double g;
            double b;
            double a;

            Color();
            Color( Color const & c );
            Color( double r, double g, double b, double a );
            virtual ~Color();

            /// Restrict all components of this color to the interval [0,1].
            void clamp();

            /// Convert this color to an intensity.
            void gray();

            /// Get the grayscale intensity of this color.
            double intensity();

            /// Randomize the RGB components of this color.
            void randomize();

            /// Generate an RBG hexadecimal string representing this color. 
            /// Generates only digits without leading 0x.
            string hex();

            double min_rgb();
            double max_rgb();
            double luminosity();
            double saturation();

            /// Compute hue for this color
            double hue();

            friend std::ostream & operator<< ( std::ostream &out, Color const &c );

            // virtual Pattern * make_pattern() const override;
            // virtual Pattern * make_concise_pattern() const override;
            virtual void serialize_to( ostream &out ) const override;
            // virtual void deserialize_from( istream &in, IParser *parser ) override;
            virtual Thing * clone() const;
            virtual string rhizome_type() const override;
            
            virtual bool has_interface( string const &w ) override;

            virtual Thing * invoke( string const &method, Thing *arg ) override;

        };



        void demo();
    }
}

#endif
