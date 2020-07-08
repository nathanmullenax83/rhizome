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
#include "core/thing.hpp"


using std::vector;
using std::string;
using std::map;
using std::function;
using std::pair;



namespace rhizome {
    namespace parse {
        
        /// Represents a compiler configuration
        class Ruleset: public Thing, public IDebuggable {
        private:
            map<string, Gramex * > rules;

        public:
            /// Create a new grammar
            Ruleset();
            virtual ~Ruleset();

            void rule( string const &w, Gramex *x );

            Gramex * lookup( string const &name ) const;
            
            virtual void dump(std::ostream &out) const override;

            // thing interface
            virtual string rhizome_type() const override;
            virtual void serialize_to( std::ostream &out ) const override;
            virtual Thing * clone() const override;
            virtual bool has_interface( string const &name ) override;
            virtual Thing *invoke( Thing *context, string const &name, Thing *arg ) override;
            
        };
    }
}

#endif
