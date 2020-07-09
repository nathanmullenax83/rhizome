#include <exception>
#include <iostream>
#include <string>
#include <cctype>
#include <map>
#include <vector>

#include "lex.hpp"
#include "log.hpp"


using std::string;
using std::map;
using std::vector;
using std::runtime_error;

namespace P = rhizome::pattern;

namespace rhizome {
    namespace lex {

        LexerState::LexerState() {

        }

        Lexer::Lexer() {
            LexerState s;
            states.push(s);
        }

        Lexer::~Lexer() {
            while( states.size() > 0 ) {
                pop_state();
            }
        }

        IPattern * Lexer::clone_pattern(string const &name) const {
            if( !states.empty() && states.top().patterns.count(name) > 0 ) {
                return states.top().patterns.at(name)->clone_pattern(false);
            } else {
                stringstream err;
                err << "Lexer does not define a rule for '" << name << "':\n";
                dump(err);
                throw runtime_error(err.str());
            }
        }

        void
        Lexer::clear() {
            states.top().streams.clear();
        }

        void
        Lexer::push_state() {
            LexerState s;
            states.push(s);
        }

        void
        Lexer::pop_state() {
            for( auto i=states.top().patterns.begin(); i!=states.top().patterns.end(); ++i) {
                delete i->second;
            }
            states.pop();
        }

        void
        Lexer::dump( ostream &out ) const {
            out << "Lexer state:\n";
            out << "\t" << "There are " << states.size() << " entries in the state stack.\n";
            out << "\t" << "The topmost entry contains the following patterns:\n";
            for( auto i=states.top().patterns.begin(); i!=states.top().patterns.end();++i) {
                Pattern *p = (Pattern*)i->second;
                if( p->valid() ) {
                    out << rhizome::ui::FG_GREEN_ON;
                } else {
                    out << rhizome::ui::FG_RED_ON;
                }
                p->serialize_to(1,out);
                out << rhizome::ui::RESET_COLOR;
                out << "\t";
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
            bool hasCharacters = !states.top().streams.empty();
            return hasCharacters;
        }

        void
        Lexer::reset_patterns() {
            auto ss = states.top();
            for( auto i=ss.patterns.begin(); i!=ss.patterns.end(); ++i) {
                i->second->reset();
            }
        }

        
        deque<Thing *>
        Lexer::peek_next_thing( size_t count, bool skipnulls ) {
            
            stringstream alltoks;
            deque<Thing*> tokens;
            while( tokens.size() < count && has_next_thing() ) {
                
                string consumed_chars;
                Thing *t = next(consumed_chars);

                // We are including NULLs intentionally.
                if( !(skipnulls && t==NULL) ) {
                    tokens.push_back(t);
                }
                alltoks << consumed_chars;
                
            }
            
            //std::cout << "Putting back: '" << alltoks.str() << "'\n";
            
            put_back(alltoks.str());
            
            return tokens;
        }

        bool
        Lexer::has_next_thing() const {
            return has_next();
        }

        bool
        Lexer::has_next_thing( string const &rule ) {
            if( !has_next()) { 
                return false; 
            }
            string putback;
            
            Thing *n = next_thing(rule,putback);
            delete n;
            put_back(putback);
            return true;
            
            
        }

        Thing *
        Lexer::next_thing(string &putback) {
            //static rhizome::log::Log log("Lexer__next_thing");
            stringstream pbb;
            string pb;

            while( has_next_thing() && (peek_next_thing(1,false))[0]==NULL ) 
                { 
                    next(pb); pbb << pb; 
                    // log.info("Skipped NULL production.\n");
                }
            if( has_next_thing() ) {
                //log.info("has_next_thing reports that there are tokens to extract.");
                Thing *t = next(pb);
                //log.info("Extracted token.");
                //log.info( t==NULL?"Token is NULL":"Token is not NULL.");
                pbb << pb;
                // if( t!=NULL ) {
                //     std::cout << "Next returned object of type " << t->rhizome_type() << " '";
                //     t->serialize_to(std::cout);
                //     std::cout << "\n";
                // }
                putback = pbb.str();
                return t;
            } else {
                putback = pbb.str();
                //log.warn("Nothing to extract.");
                return NULL;
            }
            
        }

        wchar_t
        Lexer::peek_next_character() {
            bool has_char = !states.top().streams.empty();
            assert( has_char );
            wchar_t next = states.top().streams.next();
            states.top().streams.put_back(next);
            return next;
        }

        Thing *
        Lexer::next_thing(string const &pattern_name, string &putback) {
            if( !has_next() ) {
                throw runtime_error("Nothing to extract.");
            }
            IPattern *p = states.top().patterns.at(pattern_name)->clone_pattern(false);
            p->reset();
            
            bool exit = false;
            while( has_next() && !exit ) {
                wchar_t c = peek_next_character();
                if( p->can_transition(c)) {
                    p->transition(c);
                    states.top().streams.next();
                } else {
                    exit = true;
                }
            }
            
            if( p->accepted() ) {
                putback = ((String*)p->captured_plain())->native_string();
                return p->captured_transformed();
            } else {
                stringstream err;
                err << "Expected '" << pattern_name  << "' (";
                ((Pattern*)p)->serialize_to(0,err);
                err << ")\n";
                err << "Plain capture so far: " << ((String*)p->captured_plain())->native_string();
                throw runtime_error(err.str());
            }
        }

        Thing *
        Lexer::next(string &raw_capture) {
            // reset all patterns to start state.
            reset_patterns();

            Thing *t (NULL);
            vector<string> trs;
            
            if( states.top().streams.empty()) {
                throw runtime_error("lexer::next: Stream empty");
            }
            auto &Patterns = states.top().patterns;
            // P contains everything that has been removed
            stringstream P; 

            unsigned long long int c = states.top().streams.next();
            states.top().streams.put_back(c);
            
            
            bool bail(true);
            for(auto i=Patterns.begin(); i!=Patterns.end();++i) {
                if( i->second->can_transition(c)) {
                    i->second->transition(c);
                    
                    trs.push_back(i->first);
                    bail = false;
                } else {
                    i->second->invalidate();
                }
            }

            if(!bail) {
                states.top().streams.next();
                P.put(c);
            }

            if( trs.size()==0 ) {
                stringstream err;
                err << "Character '";      
                err.put(c);
                err << "' matches no defined pattern.\n";
                
                dump( err );
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
                // keep track of the patterns that can't transition
                // in the current iteration.
                vector<string> couldnt;
                c = states.top().streams.next();
                states.top().streams.put_back(c);
                //P.put(c);
                bail = true;
                auto &dict = states.top().patterns;
                for(size_t i=0; i< trs.size(); ++i) {
                    if( dict[trs[i]]->can_transition(c)) {
                        dict[trs[i]]->transition(c);
                        next_can_transition.push_back(trs[i]);
                        bail = false;
                    } else {
                        if( dict[trs[i]]->valid()) {
                            couldnt.push_back( trs[i]);
                        }
                    }
                }
                if( next_can_transition.size() > 0 ) {
                    trs = next_can_transition;
                    P.put(c);
                    states.top().streams.next();
                    // put all patterns that couldn't match in 'invalid' state.
                    for(size_t i=0; i<couldnt.size(); ++i) {
                        dict[couldnt[i]]->invalidate();
                    }
                } else {
                    bail = true;
                }
            }
            
            
            
            bool found(false);
            for(size_t i=0; i<trs.size(); ++i) {
                auto &dict = states.top().patterns;

                if( dict[trs[i]]->accepted() ) {
                    // This may transform input, so it cannot be put back
                    // std::cout << "Lexer accepted a pattern, getting capture:\n";
                    IPattern *p = dict[trs[i]];
                    raw_capture = P.str();

                    t = p->captured_transformed();
                    //std::cout << "Got transformed capture: " << t << "\n";
                    // t may be NULL!
                    found = true;
                }
            }
            
            if( !found ) {
                throw runtime_error("No pattern accepts input.");
            }
            return t;
        }

        void
        Lexer::define( string const &name, IPattern *g ) {
            auto &ps = states.top().patterns;
            if( ps.count(name)>0 ){
                delete ps[name];
            }
            ps[name] = g;
        }

        void
        Lexer::define( string const &name, vector<string> const &keywords) {
            rhizome::pattern::Or *kws = new rhizome::pattern::Or();
            for(size_t i=0;i<keywords.size(); ++i) {
                kws->add_clause(new rhizome::pattern::Literal(keywords[i]));
            }
            define_token_type(name,kws);
        }

        void
        Lexer::define( string const &name, string const &token_literal ) {
            rhizome::pattern::Literal *lit = new rhizome::pattern::Literal(token_literal);
            define(name, lit);
        }

        void
        Lexer::put_back( string const &s ) {    
            if( s.size() > 0 ) {
                for(int i=s.size()-1; i>=0;--i) {
                    states.top().streams.put_back( s[i]);
                }
            }
        }

        void Lexer::define_token_type( string const &name, string const &literal ) {
            define_token_type( name, new rhizome::pattern::Literal(literal));
        }

        void Lexer::define_token_type( string const &name, IPattern *p ) {
            auto &patterns = states.top().patterns;
            if( patterns.count(name) > 0 ) {
                delete patterns[name];
            }
            patterns[name] = p;
        }

        void Lexer::define_ignore_whitespace() {
            define_token_type( "Whitespace", new P::Transform( P::plus(new P::Or(new P::Literal(" "),new P::Literal("\t"))),
                [a = this]( Thing *t ){
                    String *s = (String*)t;
                    if( s->native_string()=="\n" ) {
                        a->row++;
                    } else {
                        a->col++;
                    }
                    delete t;
                    return (Thing*)NULL;
                }));
            
        }


        void Lexer::undefine_token_type( string const &name ) {
            auto &patterns = states.top().patterns;
            if( patterns.count(name)) {
                delete patterns[name];
                patterns.erase(name);
            }
        }

        string Lexer::rhizome_type() const {
            return "Lexer";
        }


        void Lexer::serialize_to( size_t level, std::ostream &out ) const {
            (void)level;
            auto &patterns = states.top().patterns;
            out << rhizome_type() << "{\n";
            for( auto i = patterns.begin(); i!=patterns.end(); i++ ) {
                out << "\t" << i->first << ":\n";
                ((Pattern*)i->second)->serialize_to(level+1,out);
                out << "\n";
            }
            out << "}\n";
        }

        Thing * Lexer::clone() const {
            Lexer *copy = new Lexer(*this);
            return copy;
        }

        bool Lexer::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Thing";
        }

        Thing *
        Lexer::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)method;(void)arg; (void)context;
            throw runtime_error("Nothing to invoke.");
        }
        
    }
}