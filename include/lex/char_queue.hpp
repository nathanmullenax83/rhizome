#ifndef RHIZOME_LEX_CHAR_QUEUE_HPP
#define RHIZOME_LEX_CHAR_QUEUE_HPP

#include <deque>
#include <stdexcept>
#include "core/thing.hpp"
#include "core/i_debuggable.hpp"

using std::deque;
using std::runtime_error;

using rhizome::core::Thing;
using rhizome::core::IDebuggable;

namespace rhizome {
    namespace lex {
        /// Like a stream, but with unlimited push-back. CharQueue
        class CharQueue: public Thing, public IDebuggable {
        private:
            deque<unsigned long long int> chars;
        public:
            virtual void dump( ostream &out ) const override;
            CharQueue();

            void put_back( unsigned long long int c );
            void q( unsigned long long int c );

            bool empty() const;
            unsigned long long int next();

            virtual string rhizome_type() const override;
            virtual void serialize_to( std::ostream &out ) const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * clone() const override;

            virtual Thing * invoke( string const &method, Thing *arg ) override;

        };
    }
}

#endif
