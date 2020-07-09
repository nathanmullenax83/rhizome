#include "timeline.hpp"

namespace rhizome {
    namespace types {
        Timeline::Timeline( Time const &begin, Time const &end, Thing * context ) 
        : the_beginning(begin), the_end(end),  context(context) {

        }

        Timeline::~Timeline() {
            delete context;
        }

        string
        Timeline::rhizome_type() const {
            return "Timeline";
        }

        void
        Timeline::serialize_to( size_t level, std::ostream &out ) const {
            (void)level;
            (void)out;
            throw runtime_error("Cannot serialize a timeline, as it contains synthesized functions.");
        }

        bool
        Timeline::has_interface( string const &name ) {
            return name=="Thing"||name==rhizome_type();
        }

        Thing *
        Timeline::clone() const {
            Timeline *tl = new Timeline(the_beginning,the_end);
            tl->events = events;
            return tl;
        }

        Thing *
        Timeline::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)context;
            if( method=="clone" && arg==NULL) {
                return clone();
            }
            throw runtime_error("Not implemented.");
        }

        void
        Timeline::sync( Time t ) {
            while( pq.front() < t ) {
                Time t = pq.front();
                pq.pop();
                auto f = events.at(t);
                f(context,t);
            }
        }

        void
        Timeline::schedule(Time t, TimelineEvent listener) {
            // event chaining here. First come, first serve. Hairy.
            if( events.count(t) > 0 ) {
                auto f = events.at(t);
                events[t] = [f,listener](Thing *context, Time t) {
                    f(context,t);
                    listener(context,t);
                };
            } else {
                events[t] = listener;
            }
        }

    }
}