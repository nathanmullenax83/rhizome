#ifndef RHIZOME_TYPES_MAP_HPP
#define RHIZOME_TYPES_MAP_HPP
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "core/thing.hpp"


using std::map;
using std::string;
using std::ostream;
using std::stringstream;
using std::runtime_error;

using rhizome::core::Thing;

namespace rhizome {
    namespace types {
        class Table: public Thing {
        private:
            map< string, Thing *> rows;

        public:
            Table();

            bool contains( string const &name ) const;
            Thing * get(string const &name );
            void set( string const &name, Thing *value );
            void remove( string const &name );

            virtual void serialize_to( ostream &out ) const override;
            virtual string rhizome_type() const override;

            virtual Thing * clone() const override;
            virtual bool has_interface(string const &name) override;
            virtual Thing * invoke( string const &method, Thing *arg ) override;
        };
    }
}

#endif

