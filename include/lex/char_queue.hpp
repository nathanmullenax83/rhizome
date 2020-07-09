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
            deque<wchar_t> chars;
        public:
            virtual void dump( ostream &out ) const override;
            CharQueue();
            void clear();

            void put_back( wchar_t c );
            void q( wchar_t c );

            bool empty() const;
            wchar_t next();

            virtual string rhizome_type() const override;
            virtual void serialize_to( size_t level, std::ostream &out ) const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing * clone() const override;
            

            virtual Thing * invoke( Thing *context, string const &method, Thing *arg ) override;

        };
    }
}

#endif
