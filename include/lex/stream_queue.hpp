#ifndef RHIZOME_LEX_STREAM_QUEUE_HPP
#define RHIZOME_LEX_STREAM_QUEUE_HPP

#include <iostream>
#include <deque>
#include <sstream>
#include <string>
#include <vector>
#include "char_queue.hpp"
#include "core/i_debuggable.hpp"
#include "core/i_programmable.hpp"
#include "types/char.hpp"
#include "types/tuple.hpp"

using std::deque;
using std::istream;
using std::stringstream;
using std::string;
using std::vector;
using rhizome::core::IDebuggable;
using rhizome::core::IProgrammable;
using rhizome::types::Char;
using rhizome::types::Tuple;

namespace rhizome {
    namespace lex {

        /// A queue of stream references that appears as a single queue.
        /// Kind of like a cactus stack.
        class StreamQueue: public IProgrammable, public IDebuggable {
        private:
            deque< istream * > streams;
            CharQueue chars;

        public:
            StreamQueue();
            virtual ~StreamQueue();
            void clear();

            virtual void dump( std::ostream &out ) const override;

            void put_back( wchar_t c );
            void q( istream &str );

            
            // void bypass( istream &str );
            // void remove_bypass();
            
            bool empty() const;
            wchar_t next();

            virtual Thing * invoke( Thing *context, string const &op, Thing * arg );
        };
    }
}

#endif
