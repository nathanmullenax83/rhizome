#ifndef RHIZOME_LEX_TOKEN_QUEUE_HPP
#define RHIZOME_LEX_TOKEN_QUEUE_HPP

#include <iostream>
#include <deque>
#include <stdexcept>

#include "token.hpp"
#include "core/thing.hpp"
#include "core/i_programmable.hpp"
#include "types/bool.hpp"

using std::istream;
using std::runtime_error;
using std::deque;

using rhizome::core::Thing;
using rhizome::core::IProgrammable;
using rhizome::types::Bool;

namespace rhizome {
    namespace lex {
        class TokenQueue: public IProgrammable, public Thing {
        public:
            /// These are usually tokens.
            deque< Thing* > things;
        public:
            TokenQueue();
            virtual ~TokenQueue();

            /*
            void put_back( Token t );
            void q( Token t );  
            */
            void clear();
            /// We need this interface because the lexer emits Thing *
            void put_back( Thing * t);

            void q( Thing *t );
            
            bool empty() const;
            Thing * next();

            virtual void serialize_to(size_t level, std::ostream &out ) const override;
            virtual bool has_interface( string const &name ) override;
            virtual string rhizome_type() const override;
            virtual Thing * clone() const override;

            virtual Thing * invoke( Thing *context, string const &op, Thing *arg ) override;
        };
    }
}

#endif
