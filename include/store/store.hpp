#ifndef RHIZOME_STORE_STORE_HPP
#define RHIZOME_STORE_STORE_HPP

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "types.hpp"
#include "pattern.hpp"
#include "log.hpp"
#include "core/i_store.hpp"
#include "core/i_parser.hpp"
#include "types/dir.hpp"
#include "parse/parser.hpp"
#include "types/type_constraint.hpp"

using std::map;
using std::ostream;
using std::string;
using std::runtime_error;
using std::ofstream;
using std::ifstream;
using rhizome::core::Thing;
using rhizome::log::Log;
using rhizome::core::IStore;
using rhizome::types::Dir;
using rhizome::core::IParser;
using rhizome::parse::Parser;

namespace types = rhizome::types;

namespace rhizome {
    namespace store {

        

        /// Represents persistant storage. It is the root of a 'rhizome virtual filesystem'
        class Store: public IStore, public Thing {
        
        private:
            IParser *parser;
            // l1
            Dir root;
            // l0
            map<string,Thing *> data;

            // when something is stored on disc, it is loaded with this function
            Thing * lazy_load( string const &name );
        public:
            Store(string const &path, IParser *p);
            virtual ~Store();

            virtual void serialize_to( ostream &out ) const override;
            virtual Thing * clone() const override;
            virtual string rhizome_type() const override;
            virtual bool has_interface( string const &name ) override;

            Thing * retrieve( string const &name );
            virtual void set( string const &name, Thing *thing) override;
            virtual Thing * get( string const &name ) override;
            virtual Thing * get_clone( string const &name ) const override;
            
            virtual bool exists( string const &name ) const override;

            /// Check if something exists and satisfies type-constraint /tc/.
            virtual bool exists( string const &name, TypeConstraint *tc) const;

            virtual void remove( string const &name ) override;

            virtual Thing * invoke( Thing * context, string const &method, Thing *arg ) override;
        };
    }
}

#endif
