#ifndef RHIZOME_TYPES_TIME_HPP
#define RHIZOME_TYPES_TIME_HPP

#include <ctime>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "core/thing.hpp"
#include "core/i_time.hpp"
#include "types/expression.hpp"

using std::time_t;
using std::ostream;
using std::runtime_error;

using rhizome::core::Thing;
using rhizome::core::ITime;

namespace rhizome {
    namespace types {
        class Time: public Expression, public ITime {
        public:
            time_t t;
        
            Time();
            Time( int year, int month, int day );
            
            int year() const;
            int month() const;
            int day() const;
            int hour() const;
            int minute() const;
            int second() const;

            
            friend ostream & operator << ( ostream &out, Time const &t );
            
            /*
            virtual Pattern * make_pattern() const override;
            virtual Pattern * make_concise_pattern() const override;
            
            virtual void deserialize_from( istream &in, IParser *parser ) override;
            */

            virtual void serialize_to( ostream &out ) const override;
            virtual Thing * clone() const;


            // ITime
            virtual time_t get() const override;
            virtual bool has_interface( string const &name ) override;
            virtual string rhizome_type() const override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;
            

            // expression interface
            virtual Thing * evaluate( Thing * context ) const override;
        };

        bool operator< ( Time const &a, Time const &b ); 
    }
}

#endif