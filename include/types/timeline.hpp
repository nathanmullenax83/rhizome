#ifndef RHIZOME_TYPES_TIMELINE_HPP
#define RHIZOME_TYPES_TIMELINE_HPP

#include <map>
#include <functional>
#include <queue>

#include "core/thing.hpp"
#include "types/time.hpp"


using rhizome::core::Thing;
using rhizome::types::Time;
using std::queue;
using std::function;
using std::map;

namespace rhizome {
    namespace types {
        typedef function< void(Thing*,Time) > TimelineEvent;

        class Timeline: public Thing {
        private:
            Time the_beginning;
            Time the_end;
            Thing *context;
            map<Time,TimelineEvent> events;
            queue<Time> pq;
        public:
            Timeline( Time const &begin, Time const &end, Thing *context=NULL );
            virtual ~Timeline();

            /// Thing interface.
            string rhizome_type() const override;
            bool has_interface( string const &name ) override;
            void serialize_to( size_t level, std::ostream &out ) const override;
            Thing * clone() const override;
            Thing * invoke( Thing *context, string const &method, Thing *arg ) override;

            void schedule( Time t, TimelineEvent what );
            /// keep pulling events until we catch up to t
            void sync( Time t );
        };
    }
}

#endif