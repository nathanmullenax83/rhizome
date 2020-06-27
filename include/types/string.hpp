#ifndef RHIZOME_TYPES_STRING_HPP
#define RHIZOME_TYPES_STRING_HPP

#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "core/thing.hpp"


using std::string;
using std::ostream;
using std::stringstream;
using std::runtime_error;

using rhizome::core::Thing;

namespace rhizome {
    namespace types {
        class String: public Thing {
        private:
            std::string value;
        public:
            String();
            String( string const &v );

            friend ostream & operator << ( ostream &out, String const &s );

            // virtual rp::Pattern * make_pattern() const override;
            // virtual rp::Pattern * make_concise_pattern() const override;

            virtual void serialize_to( ostream &out ) const override;
            // virtual void deserialize_from( istream &in, IParser *parser ) override;

            virtual Thing * clone() const override;
            virtual string rhizome_type() const override;

            void append( string const &w );
            
            virtual bool has_interface(string const &name) override;
            virtual Thing * invoke( string const &method, Thing *arg ) override;

            string native_string() const;
        };
    }
}

#endif
