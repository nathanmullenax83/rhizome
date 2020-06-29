#include "dictionary.hpp"

#include <algorithm>
#include <vector>

using std::sort;
using std::vector;

namespace rhizome {
    namespace words {
        Dictionary::Dictionary() 
        :current_id(0) {

        }

        Dictionary::~Dictionary() {

        }

        size_t 
        Dictionary::bits() const {
            size_t size = counts.size();
            // find the nearest power of two
            size_t n = 1;
            while( ((size_t)(2 << n)) < size ) {
                ++n;
            }
            return n;
        }

        Integer
        Dictionary::id( string const &n ) {
            if( counts.count(n) > 0 ) {
                counts[n].first += 1;
                
            } else {
                counts[n].first = 1;
                counts[n].second = current_id++;
            }
            return counts[n].second;
        }

        void
        Dictionary::update_table() {
            string w;
            
            size_t length(0);
            size_t count(0);

            

            // auto opt_order = [&m](string w){
            //     return &m[w].first;
            // };

            // auto nat_order = [&m](string w) {
            //     return &m[w].second;
            // };
            vector< pair<string,size_t> > n;
            // Def: ideal order is count*ordinal should be kept minimal.
            //      the most concise table assigns the shortest prefix
            //      to the longest, most frequent word.
            for( auto i=counts.begin(); i!=counts.end(); i++) {
                w = i->first;
                length = i->first.size();
                count = i->second.first;
                n.push_back( pair<string,size_t>(w,count*length));
            }

            std::sort( n.begin(), n.end(),  
            []( const auto & a, const auto & b) {
                    return a.second > b.second;
                } );
            size_t new_id = 0;
            for( auto i=n.begin(); i!=n.end(); i++) {
                counts[i->first].second = new_id++;
            }
        }

        string
        Dictionary::rhizome_type() const {
            return "Dict";
        }

        void
        Dictionary::serialize_to( std::ostream &out ) const {
            out << rhizome_type();
            out << "{\n";
            for( auto i=counts.begin(); i!=counts.end(); i++) {
                out << "\t";
                out << i->first << ":" << i->second.second;
                if( i==counts.end() ) {
                    out << "\n";
                } else {
                    out << ";\n";
                }
            }
            out << "}";
        }

        bool
        Dictionary::has_interface( string const &name ) {
            return name=="Thing" || name==rhizome_type();
        }

        Thing *
        Dictionary::invoke(string const &method, Thing *arg) {
            (void)method;
            (void)arg;
            throw runtime_error("Not implemented.");
        }

        Thing *
        Dictionary::clone() const {
            Dictionary *copy = new Dictionary();
            copy->counts = counts;
            return copy;
        }
    }
}