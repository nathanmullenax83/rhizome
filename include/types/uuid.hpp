#ifndef RHIZOME_TYPES_UUID_HPP
#define RHIZOME_TYPES_UUID_HPP


#define RHIZOME_UUID_LENGTH 64

#include <string>
#include <sstream>
#include <random>
#include <stdexcept>
#include "core/thing.hpp"



using std::string;
using std::default_random_engine;
using std::uniform_int_distribution;
using std::stringstream;
using std::runtime_error;

using rhizome::core::Thing;

namespace rhizome {
    namespace types {
        static default_random_engine r;
        static uniform_int_distribution<int> dist(0,255);

        class UUID: public Thing {
        private:
            string value;
            
        public:
            UUID();

            string Value() const;

            bool operator==( UUID const &b ) const;
            virtual void serialize_to( ostream &out ) const override;
            virtual Thing * clone() const override;
            virtual string rhizome_type() const override;
            virtual bool has_interface(string const &name) override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;
        };
    }
}

#endif
