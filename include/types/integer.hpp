#ifndef RHIZOME_TYPES_INTEGER_HPP
#define RHIZOME_TYPES_INTEGER_HPP

#include <gmp.h>
#include <gmpxx.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>

#include "core/thing.hpp"

using rhizome::core::Thing;

using std::string;
using std::runtime_error;
using std::ostream;
using std::stringstream;

namespace rhizome {
    namespace types {
        class Integer: public Thing {
        private:
            mpz_class value;

        public:
            Integer();
            Integer( int value );
            Integer( string const &value );
            Integer( mpz_class value );

            bool is_prime();

            long int native_int() const;

            friend ostream & operator << ( ostream &out, Integer const &j );
            /*
            virtual rp::Pattern * make_pattern() const override;
            virtual rp::Pattern * make_concise_pattern() const override;'
            */

            friend bool operator< ( Integer const &a, Integer const &b );
            friend bool operator> ( Integer const &a, Integer const &b );
            friend bool operator!= (Integer const &a, Integer const &b );
            friend Integer operator+ ( Integer const &a, Integer const &b );
            friend Integer operator- ( Integer const &a, Integer const &b );
            friend Integer operator/ ( Integer const &a, Integer const &b );
            friend Integer operator* ( Integer const &a, Integer const &b );
            friend bool operator== (Integer const &a, Integer const &b );

            virtual void serialize_to( ostream &out ) const override;
            /*
            virtual void deserialize_from( istream &in, IParser *parser ) override;*/

            virtual Thing * clone() const;

            virtual string rhizome_type() const;
            

            
            virtual bool has_interface( string const &name );
            virtual Thing * invoke( string const &method, Thing *arg ) override;

        };

        
    }
}

#endif
