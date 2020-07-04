#ifndef RHIZOME_ALPHABET_CLASSIFIER_HPP
#define RHIZOME_ALPHABET_CLASSIFIER_HPP

#include <cwctype>

#include <locale>
#include <codecvt>
#include <string>
#include <map>
#include <set>
#include <functional>
#include <cassert>

using std::string;
using std::map;
using std::function;
using std::set;

#include "core/thing.hpp"
#include "types/tuple.hpp"
#include "types/char.hpp"
#include "types/string.hpp"

using rhizome::core::Thing;
using rhizome::types::Tuple;
using rhizome::types::String;
using rhizome::types::Char;

namespace rhizome {
    namespace alphabet {
        /// Classifier is going to be the basis for the second revision
        /// of the programmable lexer. It is elsewhere referred to as 
        /// a 'sublexer'. 
        class Classifier: public Thing {
        private:
            map< string, function< bool( unsigned long long) > > fns;

            
        public:
            Classifier();
            ~Classifier();

            // Expensive. Really a reference function.
            set< string > classes( unsigned long long c ) const;

            // Much more efficient!
            bool member( string const &name, unsigned long long c ) const;

            // function constructors:
            // 1st order functions
            void define_range( string const &name, unsigned long long begin, unsigned long long end );

            // define a named set of characters 
            // UTF8 string @characters will be widened!
            void define_set( string const &name, string const &characters );
            void define_set( string const &name, function< bool(unsigned long long) > p_member);

            // 2nd order functions
            void define_union( string const &name, string const &first, string const &second );
            void define_union( string const &name, vector<string> const &cs );

            void define_intersection( string const &name, string const &first, string const &second );
            void define_intersection( string const &name, vector<string> const &cs );

            void define_difference( string const &name, string const &first, string const &second );
            void define_complement( string const &name, string const &a );

            // Thing interface
            virtual Thing * invoke( Thing *context, string const &method, Thing * arg ) override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * clone() const override;
            virtual void serialize_to( std::ostream &out ) const override;
            virtual string rhizome_type() const override;
        };

        /// Create system default classifier.
        Classifier * create_rhizome_classifier();
    }
}

#endif