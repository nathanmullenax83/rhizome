#include "stream_queue.hpp"


namespace rhizome {
    namespace lex {

        StreamQueue::StreamQueue() {

        }

        StreamQueue::~StreamQueue() {
            
        }

        void
        StreamQueue::clear() {
            streams.clear();
            chars.clear();
        }

        void
        StreamQueue::dump( ostream &out ) const {
            out << "The stream queue first draws from a put-back buffer\n.";
            if( chars.empty() ) {
                out << "\tThat buffer is currently empty.\n";
            } else {
                out << "\tThat buffer contains the following characters.\n";
                chars.dump(out);
            }
        }

        void 
        StreamQueue::q( istream &str ) {
            streams.push_back(&str);
        }

        // void
        // StreamQueue::bypass( istream &str ) {
        //     streams.push_front( &str );
        // }

        // void
        // StreamQueue::remove_bypass() {
        //     if( !streams.empty() ) {
        //         streams.pop_front();
        //     } else {
        //         throw new runtime_error("No bypass to remove.");
        //     }
        // }

        bool
        StreamQueue::empty() const {
            if( !chars.empty() ) {
                return false;
            }
            if( streams.size()==0 ) {
                return true;
            } else {
                for( size_t i=0; i<streams.size(); ++i) {
                    if( streams[i]->good() && (streams[i]->rdbuf()->in_avail()>0)) {
                        return false;
                    }
                }
            }
            return true;
        }

        wchar_t
        StreamQueue::next() {
            if( ! chars.empty() ) {
                return chars.next();
            }
            if( !empty() ) {
                while( streams.size()>0 ) {
                    if( streams.front()->rdbuf()->in_avail() > 0 ) {
                        return streams.front()->get();
                    } else {
                        streams.pop_front();
                    }
                }
            }
            throw runtime_error("No characters available.");
        }

        void
        StreamQueue::put_back( unsigned long long int c ) {
            chars.put_back(c);
        }

        Thing *
        StreamQueue::invoke( Thing *context, string const &op, Thing *arg ) {
            (void)context;
            if( op=="put_back" && arg->rhizome_type()=="Char") {
                Char *c = (Char*)(arg);
                put_back(c->v); return NULL;
            } else if( op=="dump" ) {
                dump(std::cout); return NULL;
            } else if( op=="next" ) {
                Char *c = new Char( next());
                return c;
            } else {
                throw runtime_error("Invalid invocation.");
            }
            
        }
    }
}