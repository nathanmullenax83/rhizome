#ifndef RHIZOME_PATTERN_N_TIMES_HPP
#define RHIZOME_PATTERN_N_TIMES_HPP

#include <stdexcept>
#include "pattern.hpp"

using std::runtime_error;

namespace rhizome {
    namespace pattern {
        /// Match a subexpression some number of times
        class NTimes: public Pattern {
        private:
            size_t N;
            size_t n;
            IPattern *inner;
            stringstream xd;
        public:
            NTimes(size_t N, IPattern *inner);
            virtual ~NTimes();

            virtual void reset();
            virtual bool can_transition(char c) const;
            virtual void transition(char c);
            virtual bool accepted() const;

            virtual IPattern * clone_pattern(bool withstate) const override;
            virtual void serialize_to( ostream &out ) const;

            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;
            virtual Thing * captured_plain() override;
            virtual Thing * captured_transformed() override;
        };
    }
}

#endif
