#ifndef RHIZOME_TYPES_HAS_INTERFACE_HPP
#define RHIZOME_TYPES_HAS_INTERFACE_HPP

#include "types/type_constraint.hpp"
#include "types/bool.hpp"

using rhizome::types::TypeConstraint;
using rhizome::types::Bool;

namespace rhizome {
    namespace types {
        class HasInterface: public TypeConstraint {
        private:
            string interface_name;
        public:
            HasInterface( string const &name );
            // type-contraint interface
            virtual bool contains( Thing *arg ) const override;

            // thing interface
            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &method ) override;
            virtual void serialize_to( std::ostream &out ) const override;
            virtual Thing * clone() const override;
            virtual Thing * invoke ( string const &method, Thing *arg) override;
        };
    }
}

#endif