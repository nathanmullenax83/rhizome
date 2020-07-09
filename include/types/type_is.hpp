#ifndef RHIZOME_TYPES_TYPE_IS 
#define RHIZOME_TYPES_TYPE_IS

#include <string>
using std::string;

#include "core/thing.hpp"
#include "type_constraint.hpp"

namespace rhizome {
    namespace types {
        class TypeIs: public TypeConstraint {
        private:
            string type_name;
        public:
            TypeIs( string const &tn );

            virtual bool contains( Thing *t ) const override;

            // interface specific clone

            // thing interface
            virtual string rhizome_type() const override;
            virtual void serialize_to(size_t level,std::ostream &out) const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg );
            virtual Thing * clone() const override;

        };
    }
}

#endif