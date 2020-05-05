#ifndef RHIZOME_PARSE_RULESET_HPP
#define RHIZOME_PARSE_RULESET_HPP

#include <vector>
#include <map>
#include <string>
#include <functional>
#include <tuple>
#include "gramex.hpp"
#include "core/i_parser.hpp"


using std::vector;
using std::string;
using std::map;
using std::function;
using std::pair;



namespace rhizome {
    namespace parse {
        typedef function< Thing * ( deque<Thing*> ) > ParseFn;
        /// Represents a compiler configuration
        class Ruleset {
        private:
            map<string, pair<Gramex *, ParseFn> > rules;

        public:
            /// Create a new grammar
            Ruleset();
            virtual ~Ruleset();

            void rule( string const &w, Gramex *x, ParseFn f );

            Gramex * lookup( string const &name ) const;
            ParseFn lookup_parser( string const &name ) const;
            

            
        };
    }
}

#endif
