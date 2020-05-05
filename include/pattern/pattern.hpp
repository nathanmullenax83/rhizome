#ifndef RHIZOME_PATTERN_HPP
#define RHIZOME_PATTERN_HPP

#include <iostream>
#include <stdexcept>
#include <string>
#include "core/thing.hpp"
#include "core/i_pattern.hpp"



using std::string;
using std::ostream;
using std::runtime_error;

using rhizome::core::Thing;
using rhizome::core::IPattern;

namespace rhizome {
    namespace pattern {
        class Pattern: public Thing, public IPattern {
        protected:
            bool _valid;
        public:
            Pattern();
            virtual ~Pattern();

            // override core::IPattern
            virtual bool accepts( string const &w ) override;
            
            virtual void reset();

            
            virtual void invalidate() override;
            virtual bool valid() const override;

            
            virtual Thing * clone() const override;


            
        };

        
    }
}

#endif
