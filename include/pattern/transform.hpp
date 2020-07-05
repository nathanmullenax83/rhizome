#ifndef RHIZOME_PATTERN_TRANSFORM_HPP
#define RHIZOME_PATTERN_TRANSFORM_HPP

#include <functional>
#include "pattern.hpp"
#include "core/i_verifiable.hpp"

using std::function;

using rhizome::core::IVerifiable;

namespace rhizome {
    namespace pattern {
        typedef function< Thing*(Thing*) > TokenConstructor;

        class Transform: public Pattern, public  IVerifiable{
        private:
            IPattern *inner;
            TokenConstructor transform;
        public:
            Transform(IPattern *inner, TokenConstructor transform);
            virtual ~Transform();

            virtual void reset();
            virtual bool can_transition(char c) const;
            virtual void transition(char c);
            virtual bool accepted() const;

            virtual IPattern * clone_pattern(bool withstate) const override;
            virtual void serialize_to( ostream &out ) const override;
            

            virtual string rhizome_type() const override;
            virtual bool has_interface(string const &name) override;
            virtual Thing * invoke( Thing *context, string const &method, Thing * arg ) override;
            virtual Thing * captured_plain() override;
            virtual Thing * captured_transformed() override;
            virtual bool verify(std::ostream &out) override;
            
        };

    }
}

#endif
