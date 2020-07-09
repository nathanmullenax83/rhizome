#ifndef RHIZOME_CORE_SYSTEM_HPP
#define RHIZOME_CORE_SYSTEM_HPP

#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <tuple>
#include "i_parser.hpp"
#include "i_store.hpp"
#include "thing.hpp"

using std::map;
using std::string;
using std::function;
using std::deque;
using std::pair;
using rhizome::core::Thing;
using rhizome::core::IParser;
using rhizome::core::IStore;

namespace rhizome {
    namespace core {
        
        
        typedef function< Thing*(Thing *) > Factory;
        typedef function< Thing*(void) > UnitFactory;
        typedef function< void(IParser*) > ParserSideEffect;
        typedef pair< string, ParserSideEffect > RuleConstructor;

        /// A system is a complex of machines, classified by type.
        class System: public Thing {
        private:
            IParser *parser;
            IStore *store;
            vector< RuleConstructor > journal;
            map< string, Factory > higher_order_constructors;
            map< string, UnitFactory > simple_factories;
            
        public:
            System(IParser *parser, IStore *store);
            virtual ~System();

            virtual void serialize_to(size_t level, std::ostream &out) const override;
            virtual bool has_interface( string const &name ) override;
            virtual string rhizome_type() const override;
            virtual Thing * clone() const override;
            virtual Thing * invoke(Thing *context,  string const &method, Thing *arg ) override;
            
            void register_type( string const &name, Factory ctor, ParserSideEffect make_rule ) ;
            void register_type( string const &name, UnitFactory ctor, ParserSideEffect make_rule );

            // you can access the parser directly, if need be
            IParser * get_parser();

            // you can also use this shortcut to get the lexer
            ILexer * get_lexer();

            // or use this punch-through to parse by a particular starting rule.
            Thing * parse_thing( string const &start_rule );
            
            // or this one, if you are parsing from a particular source (say, a filestream)
            Thing * parse_thing( string const &start_rule, std::istream &in);

            

        };

        
    }
}



#endif
