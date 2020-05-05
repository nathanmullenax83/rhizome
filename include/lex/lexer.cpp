#include <exception>
#include <iostream>
#include <string>
#include <cctype>
#include <map>
#include <vector>

#include "lex.hpp"


using std::string;
using std::map;
using std::vector;
using std::runtime_error;

namespace rhizome {
    namespace lex {

        Lexer::Lexer() {
            LexerState s;
            states.push(s);
        }

        Lexer::~Lexer() {
            while( states.size() > 0 ) {
                pop_state();
            }
        }

        void
        Lexer::push_state() {
            LexerState s;
            states.push(s);
        }

        void
        Lexer::pop_state() {
            for( auto i=states.top().patterns.begin(); i!=states.top().patterns.end(); ++i) {
                delete i->second.pattern;
            }
            states.pop();
        }

        void
        Lexer::dump( ostream &out ) const {
            out << "Lexer state:\n";
            out << "\t" << "There are " << states.size() << " entries in the state stack.\n";
            out << "\t" << "The topmost entry contains the following patterns:\n";
            for( auto i=states.top().patterns.begin(); i!=states.top().patterns.end();++i) {
                i->second.pattern->serialize_to(out);
                out << "\t";
            }
            
            if( !states.top().tokens.things.empty()) {
                out << "\t" << "The token queue (put_back tokens) contains:\n";
                for(size_t i=0; i<states.top().tokens.things.size(); ++i) {
                    out << "\t\t";
                    states.top().tokens.things[i]->serialize_to(out);
                    out << " [type: ";
                    out << states.top().tokens.things[i]->rhizome_type() << "]\n";

                }
            } else {
                out << "\tThe token queue is empty.\n";
            }
            out << "\t" << "The stream_queue buffers characters.\n";
            states.top().streams.dump(out);
        }

        void
        Lexer::q( istream &str ) {
            states.top().streams.q(str);
        }

        bool
        Lexer::has_next() const {
            bool hasQueuedTokens = !states.top().tokens.empty();
            bool hasCharacters = !states.top().streams.empty();

            return hasQueuedTokens || hasCharacters;
        }

        bool
        Lexer::direct_has_next( istream &in ) {
            return in.peek() != EOF;
        }

        Thing *
        Lexer::direct_next( istream &in ) {
            states.top().streams.bypass(in);
            Thing *t = next();
            states.top().streams.remove_bypass();
            return t;
        }

        

        void
        Lexer::reset_patterns() {
            auto ss = states.top();
            for( auto i=ss.patterns.begin(); i!=ss.patterns.end(); ++i) {
                i->second.pattern->reset();
            }
        }

        Thing *
        Lexer::peek_next_thing( size_t index ) {
            while( states.top().tokens.things.size() < index+1 ) {
                states.top().tokens.q( next(true) );
            }
            Thing *nt = states.top().tokens.things[index];
            return nt->clone();
        }

        bool
        Lexer::has_next_thing() const {
            return has_next();
        }

        Thing *
        Lexer::next_thing() {
            
            while( has_next_thing() && peek_next_thing(0)==NULL ) 
                { next(false);}
            if( has_next_thing() ) {
                Thing *t = next(false);
                return t;
            } else {
                throw runtime_error("Nothing to extract.");
            }
            
        }

        Thing *
        Lexer::next(bool skipcheck) {

            // first check for queued tokens
            if( !skipcheck && !states.top().tokens.empty() ) {

                return states.top().tokens.next()->clone();
            }
            // reset all patterns to start state.

            reset_patterns();


            
            Thing *t (NULL);
            vector<string> trs;
            
            if( states.top().streams.empty()) {
                throw runtime_error("lexer::next: Stream empty");
            }
            auto &ps = states.top().patterns;
            unsigned long long int c = states.top().streams.next();
            bool bail(true);
            for(auto i=ps.begin(); i!=ps.end();++i) {
                if( i->second.pattern->can_transition(c)) {
                    i->second.pattern->transition(c);
                    trs.push_back(i->first);
                    bail = false;
                }
            }

            if( trs.size()==0 ) {
                std::cout << "Received: '" << (char)c << '\n';
                dump( std::cout );
                throw runtime_error("Character matches no defined pattern.");
            }

            // if there are no more characters and nothing 
            // has excepted yet, throw an appropriate error!
            if( states.top().streams.empty() && trs.size()==0) {
                throw runtime_error("No more characters.");
            }
            
            if( bail ) {
                throw new runtime_error("Unrecognized token.");
            }
            
            
            while( !bail && trs.size() > 0 && !states.top().streams.empty() ) {
                vector<string> next_can_transition;
                c = states.top().streams.next();
                bail = true;
                auto &dict = states.top().patterns;
                for(size_t i=0; i< trs.size(); ++i) {
                    if( dict[trs[i]].pattern->can_transition(c)) {
                        dict[trs[i]].pattern->transition(c);
                        next_can_transition.push_back(trs[i]);
                        bail = false;
                    } 
                }
                if( next_can_transition.size() > 0 ) {
                    trs = next_can_transition;

                } else {
                    states.top().streams.put_back(c);
                    bail = true;
                }
            }
            
            
            bool found(false);
            for(size_t i=0; i<trs.size(); ++i) {
                auto &dict = states.top().patterns;

                if( dict[trs[i]].pattern->accepted() ) {
                    Token *token = new Token(); 
                    token->set( dict[trs[i]].pattern->captured(), trs[i], 0,0);
                    t = dict[trs[i]].ctor( token );
                    found = true;
                }
            }
            
            if( !found ) {
                throw runtime_error("No pattern accepts input.");
            }
            return t;
        }

        void
        Lexer::define( string const &name, rhizome::pattern::Group *g ) {
            PatternRecord rec;
            // Identity function.
            rec.ctor = [] ( IToken *t ) {
                // This will return NULL is it's not a valid cast.
                return dynamic_cast<Thing*>(t);
            };
            rec.pattern = g;
            auto &ps = states.top().patterns;
            if( ps.count(name)>0 ){
                delete ps[name].pattern;
            }
            ps[name] = rec;
        }

        void
        Lexer::define( string const &name, vector<string> const &keywords) {
            
            rhizome::pattern::Or *kws = new rhizome::pattern::Or();
            for(size_t i=0;i<keywords.size(); ++i) {
                kws->add_clause(new rhizome::pattern::Literal(keywords[i]));
            }
            
            define_token_type(name,kws, []( IToken *t) {
                return new String(t->token_value());
            });
        }

        void
        Lexer::define( string const &name, string const &token_literal ) {
            rhizome::pattern::Literal *lit = new rhizome::pattern::Literal(token_literal);
            define(name, new rhizome::pattern::Group(lit));
        }

        // void
        // Lexer::put_back( Token t ) {
        //     states.top().tokens.put_back(t);
        // }

        void
        Lexer::put_back_thing( Thing *t ) {
            states.top().tokens.put_back(t);
        }

        void Lexer::define_token_type( string const &name, IPattern *p, function< Thing*(IToken*) > ctor ){
            auto &patterns = states.top().patterns;
            // If there's a record, delete the pattern
            if( patterns.count(name) > 0) {
                delete patterns[name].pattern;
            }

            PatternRecord pr;
            pr.pattern = new rhizome::pattern::Group(p);
            pr.ctor = ctor;
            patterns[name] = pr;
        }

        void Lexer::define_token_type( string const &name, string const &literal ) {
            define_token_type( name, new rhizome::pattern::Literal(literal),[](IToken *t){
                return new rhizome::types::String(t->token_value());
            });
        }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
        void Lexer::define_token_type( string const &name, IPattern *p, function <Thing*(void)> ctor ) {
            define_token_type( name, p, [ctor](IToken *t){
                return ctor();
            });
        }
#pragma GCC diagnostic pop

        void Lexer::undefine_token_type( string const &name ) {
            auto &patterns = states.top().patterns;
            if( patterns.count(name)) {
                delete patterns[name].pattern;
                patterns.erase(name);
            }
        }

        string Lexer::rhizome_type() const {
            return "Lexer";
        }


        void Lexer::serialize_to( std::ostream &out ) const {
            out << rhizome_type() << "(";
            out << ")";
        }

        Thing * Lexer::clone() const {
            Lexer *copy = new Lexer(*this);
            return copy;
        }

        bool Lexer::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Thing";
        }
        
    }
}