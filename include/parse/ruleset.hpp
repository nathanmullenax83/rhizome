#ifndef RHIZOME_PARSE_RULESET_HPP
#define RHIZOME_PARSE_RULESET_HPP

#include <vector>
#include <map>
#include <string>
#include <functional>
#include <tuple>
#include "gramex.hpp"
#include "core/i_parser.hpp"
#include "core/i_debuggable.hpp"


using std::vector;
using std::string;
using std::map;
using std::function;
using std::pair;



namespace rhizome {
    namespace parse {
        
        /// Represents a compiler configuration
        class Ruleset: public IDebuggable {
        private:
            map<string, Gramex * > rules;

        public:
            /// Create a new grammar
            Ruleset();
            virtual ~Ruleset();

            void rule( string const &w, Gramex *x );

            Gramex * lookup( string const &name ) const;
            
            virtual void dump(std::ostream &out) const override;

            
        };
    }
}

#endif
