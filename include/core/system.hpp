#ifndef RHIZOME_CORE_SYSTEM_HPP
#define RHIZOME_CORE_SYSTEM_HPP

#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <tuple>
#include "i_parser.hpp"
#include "i_store.hpp"
#include "machine.hpp"


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
        typedef function<Thing*(istream &in, IParser*)> CTor;


        /// A system is a complex of machines, classified by type.
        class System: public Thing {
        private:
            IParser *parser;
            IStore *store;
        public:
            System(IParser *parser, IStore *store);
            virtual ~System();

            virtual void serialize_to(std::ostream &out) const override;
            virtual bool has_interface( string const &name ) override;
            virtual string rhizome_type() const override;
            virtual Thing * clone() const override;
            virtual Thing * invoke( string const &method, Thing *arg ) override;
            
            
        };
    }
}

#endif
