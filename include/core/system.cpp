#include "system.hpp"

namespace rhizome {
    namespace core {
        System::System(IParser *parser, IStore *store): parser(parser), store(store) {
            
        }

        System::~System() {
            delete parser;
            delete store;
        }

        string
        System::rhizome_type() const {
            return "System";
        }

        void 
        System::serialize_to( std::ostream &out ) const {
            out << rhizome_type() << "{";
            out << "}";
        }

        Thing *
        System::clone() const {
            Thing *unsafe = (Thing*)parser;
            IParser *parser_clone = (IParser*) unsafe->clone();
            Thing *unsafe_store = (Thing*)store;
            IStore *store_clone = (IStore*)unsafe_store->clone();
            System *copy = new System(parser_clone,store_clone);
            return copy;
        }

        bool
        System::has_interface( string const &name ) {
            return name==rhizome_type() || name=="Thing";
        }

        Thing *
        System::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)context;
            if( arg==NULL ) {
                if( method=="clone" ) {
                    return clone();
                } else if( method=="type" ) {
                    
                } else if( method=="parse") {
                    stringstream ss;
                    arg->serialize_to(ss);
                    return parser->parse_thing( ss.str() );
                }
            }
            throw runtime_error("Not implemented.");
        }

        IParser *
        System::get_parser() {
            return parser;
        }

        ILexer *
        System::get_lexer() {
            return parser->get_lexer();
        }
        
        void
        System::register_type( string const &name, Factory ctor, ParserSideEffect shim ) {
            shim(parser);
            journal.push_back( RuleConstructor(name,shim) );
            higher_order_constructors[name] = ctor;
        }

        void 
        System::register_type( string const &name, UnitFactory ctor, ParserSideEffect shim) {
            shim(parser);
            journal.push_back( RuleConstructor(name,shim));
            simple_factories[name] = ctor;
        }


        Thing *
        System::parse_thing( string const &start_rule ) {
            return parser->parse_thing(start_rule);
        }

        Thing *
        System::parse_thing( string const &start_rule, std::istream &in ) {
            parser->q_stream(in);
            return parser->parse_thing( start_rule );
        }

        
    }
}