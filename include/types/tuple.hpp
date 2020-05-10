#ifndef RHIZOME_TYPES_TUPLE_HPP
#define RHIZOME_TYPES_TUPLE_HPP

#include <deque>
#include <string>
#include <tuple>
#include "core/thing.hpp"
#include "pattern.hpp"

using std::deque;
using std::string;
using std::pair;
using rhizome::pattern::Pattern;
using rhizome::core::Thing;

namespace rhizome {
    namespace types {
        
        /// Represent an ordered set of things
        /// with no particular type constraint.
        class Tuple: public Thing {
        private:
            deque< Thing* > items;
        public:
            Tuple();
            virtual ~Tuple();
            
            /// Augment this 
            void append( Thing *item );
            void prepend( Thing *item );
            size_t size() const;

            Thing * at( size_t i );

            // Thing interface
            virtual void serialize_to( ostream &out ) const override;
            virtual Thing * clone() const override;
            virtual string rhizome_type() const override;
            virtual bool has_interface(string const &name) override;
            virtual Thing * invoke( string const &method, Thing *arg ) override;

        };
    }
}

#endif