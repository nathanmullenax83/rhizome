#ifndef RHIZOME_TYPES_VTABLE_HPP
#define RHIZOME_TYPES_VTABLE_HPP

#include <map>
#include <string>
#include <stdexcept>
#include "core/thing.hpp"
#include "types/tuple.hpp"
#include "types/type_constraint.hpp"

using std::map;
using std::string;
using std::runtime_error;
using rhizome::core::Thing;
using rhizome::types::Tuple;
using rhizome::types::TypeConstraint;

namespace rhizome {
    namespace types {
        /// signature -> hash of named things
        typedef map< string, map<string, Thing *> > VTableData;
        

        /// This is for storing a bunch of functions
        class VTable: public Thing {
        private:
            VTableData vtable;

        public:
            VTable();

            /// Lookup something by signature and type.
            Thing * lookup( string const &signature, string const &name );

            /// Lookup a set of things by signature alone.
            Tuple * lookup( string const &signature );

            /// Add something to the table
            void insert( string const &name, Thing *t );

            string rhizome_type() const override;
            void serialize_to( size_t level, std::ostream &out ) const override;
            bool has_interface( string const &name ) override;
            Thing * invoke( Thing *context, string const &method, Thing *arg ) override;
            Thing * invoke( Thing *context, string const &method );
            Thing * invoke_x( Thing *context, string const &method, Thing *arg, TypeConstraint *arg_constraint);

            
            Thing * clone() const override;
            
        };
    }
}

#endif