#ifndef RHIZOME_TYPES_TUPLE_HPP
#define RHIZOME_TYPES_TUPLE_HPP

#include <deque>
#include <string>
#include <tuple>
#include "core/thing.hpp"
#include "pattern.hpp"
#include "types/expression.hpp"

using std::deque;
using std::string;
using std::pair;
using rhizome::pattern::Pattern;
using rhizome::core::Thing;
using rhizome::types::Expression;

namespace rhizome {
    namespace types {
        
        /// Represent an ordered set of things
        /// with no particular type constraint.
        class Tuple: public Expression {
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
            virtual void serialize_to( size_t indent, ostream &out ) const override;
            virtual Thing * clone() const override;
            virtual string rhizome_type() const override;
            virtual bool has_interface(string const &name) override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;

            // list processing
            /// Remove the first element, modifying the tuple in the process.
            Thing * extract_first();
            /// Remove the last element, modifying the list in the process.
            Thing * extract_last();

            // bridge methods
            vector<string> get_vector_of_native_strings();

            // expression interface
            virtual Thing * evaluate( Thing *context ) const override;
        };
    }
}

#endif