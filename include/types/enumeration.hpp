#ifndef RHIZOME_TYPES_ENUMERATION_HPP
#define RHIZOME_TYPES_ENUMERATION_HPP

#include <map>
#include "core/thing.hpp"
#include "integer.hpp"

using std::map;
using rhizome::core::Thing;

namespace rhizome {
    namespace types {
        class Enumeration: public Thing {
        private:
            map< Integer, Thing * > data;
        public:
            void set( Integer n, Thing *element );
            Thing * get( Integer n );
            Thing * get_clone( Integer n ) const;

            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
            virtual void serialize_to( std::ostream &out ) const override;
            virtual Thing * clone() const override;
            virtual Thing * invoke( string const &method, Thing *arg ) override;

        };
    }
}

#endif
