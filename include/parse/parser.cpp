#include "parser.hpp"

namespace rhizome {
    namespace parse {
        Group *
        decimal_pattern() {
            pat::Cat *c = new pat::Cat();
            c->append( new pat::Plus( new pat::Digit() ));
            c->append( new pat::Literal("."));
            c->append( new pat::Plus( new pat::Digit() ));
            return new pat::Group(c);
        }

        Group *
        integer_pattern() {
            pat::Plus *p = new pat::Plus( new pat::Digit() );
            return new pat::Group(p);
        }

        Group *
        string_pattern() {
            pat::Cat *c = new pat::Cat();
            c->append(new pat::Literal("\""));
            c->append( new pat::Literal("\""));
            return new pat::Group(c);
        }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
        Parser::Parser() {
            types::Float float_proto(0.0);
            types::Integer int_proto(0);
            types::String string_proto("");

            lexer.define_token_type( "Whitespace", new Group(new pat::Whitespace()),
                []( IToken *t ){
                    return (Thing*)NULL;
                });
            lexer.define_token_type( "Float", decimal_pattern(),
                []( IToken *t ) {
                    return new rhizome::types::Float(t->token_value());
                });
            lexer.define_token_type( "Integer", integer_pattern(),
                []( IToken *t ) {
                    return new rhizome::types::Integer(t->token_value());
                });
            lexer.define_token_type( "String", string_pattern(),
                []( IToken *t )     {
                    return new rhizome::types::String(t->token_value());
                });
            
            lexer.define_token_type( "OParen", "(");
            lexer.define_token_type( "CParen", ")");
            lexer.define_token_type( "OBrack", "{");
            lexer.define_token_type( "CBrack", "}");
            lexer.define_token_type( "Comma", ",");
            lexer.define_token_type( "Colon", ":");
            lexer.define_token_type( "Semicolon", ";");
            lexer.define_token_type( "Plus", "+");
            lexer.define_token_type( "Minus", "-");
            lexer.define_token_type( "Times", "*");
            lexer.define_token_type( "Div", "/");
            lexer.define_token_type( "Dot", ".");
            lexer.define_token_type( "Bareword", 
                    new pat::Cat(
                        new pat::Plus( new pat::Alpha() ),
                        new pat::Star( new pat::Or( new pat::Alpha(), new pat::Digit() ))
                    )
                ,[](IToken *t) {
                    return new rhizome::types::String(t->token_value());
                });
        }
#pragma GCC diagnostic pop

        void
        Parser::rule( string const &w, Gramex *g ) {
            rules.rule(w,g);
        }


        string Parser::match_integer( istream &in ) {
            if( lexer.direct_has_next(in)) {
                Thing *p = lexer.direct_next(in);

                if(  p->rhizome_type() != "Integer") {
                    stringstream err;
                    err << "Expected integer, but encounted " << p->rhizome_type();
                    delete p;
                    throw runtime_error(err.str());
                } else {
                    stringstream t;
                    p->serialize_to(t);
                    delete p;
                    return t.str();
                }
            } else {
                throw runtime_error("Expected integer, but reached end of stream.");
            }
        }

        string Parser::match_float( istream &in ) {
            if( lexer.direct_has_next(in)) {
                Thing *temp = lexer.direct_next(in);
                
                if( temp->rhizome_type() != "Float") {
                    stringstream err;
                    err << "Expected float, but encountered " << temp->rhizome_type();
                    throw runtime_error(err.str());
                } else {
                    stringstream v;
                    temp->serialize_to(v);
                    delete temp;
                    return v.str();
                }
            } else {
                throw runtime_error("Expected float, but reach end of stream.");
            }
        }

        string Parser::match_pattern( istream &in, Pattern *p ) {
            // p is some sort of ad-hoc token. 
            lexer.push_state();
            lexer.define_token_type("AdHocToken", p, [](IToken*t){ return new rhizome::types::String(t->token_value()); });
            lexer.q(in);
            Thing *temp = lexer.next();
            stringstream v;
            temp->serialize_to(v);
            delete temp;
            lexer.pop_state();
            return v.str();
        }

        string Parser::match_qstring( istream &in ) {
            if( lexer.direct_has_next(in)) {
                Thing *temp = lexer.direct_next(in);
                stringstream v;
                temp->serialize_to(v);
                delete temp;
                if( temp->rhizome_type() != "String") {
                    stringstream err;
                    err << "Expected string, but encountered " << temp->rhizome_type();
                    throw runtime_error(err.str());
                } else {
                    return v.str();
                }
            } else {
                throw runtime_error("Expected string, but reach end of stream.");
            }
        }

        string Parser::match_literal( istream &in, string const &w ) {
#ifdef INSTRUMENTED
            std::cout << "Attempting to match literal " << w << "\n";
#endif
            if( lexer.direct_has_next(in)) {
#ifdef INSTRUMENTED
                std::cout << "The stream is not empty (direct).\n";
#endif
                Thing *temp = lexer.direct_next(in);
                stringstream v;
                temp->serialize_to(v);
                string v_str = v.str();
                //delete temp;
#ifdef INSTRUMENTED
                std::cout << "Extracted token: " << v_str << "\n";
#endif
                if( v_str != w) {
                    stringstream err;
                    err << "Expected '" << w << "' but encountered '" << v_str;
                    throw runtime_error(err.str());
                } else {
                    return v_str;
                }
            } else {
                stringstream err;
                err << "Expected '" << w << "' but encountered end of stream.";
                throw runtime_error(err.str());
            }
        }

        IGramex *
        Parser::lookup( string const &name ) const {
            return rules.lookup(name);
        }

        Thing *
        Parser::parse_thing( string const &start_rule ) {
            
            IGramex *start = lookup(start_rule);
#ifdef INSTRUMENTED
            std::cout << "-- Start rule: ";
            ((Gramex*)start)->serialize_to(std::cout);
            std::cout << "\n";
#endif
            
            GrammarFn static_lookup = [this]( string const &name ) { return this->lookup(name);};
            start->match( &lexer, static_lookup );

            auto ts = start->clone_matched_tokens();
            if( ts.size() > 1 ) {
                Tuple *results = new Tuple();
                            
                for( auto i =ts.begin(); i!=ts.end(); i++) {
                    results->append(*i);
                }
                return results;
            } else {
                return ts[0];
            }
        }

        void
        Parser::q_stream( istream &in ) {
            lexer.q(in);
        }

        void
        Parser::serialize_to( std::ostream &out ) const {
            out << rhizome_type() << "{";
            out << "}";
        }

        string
        Parser::rhizome_type() const {
            return "Parser";
        }

        bool
        Parser::has_interface(string const &name) {
            return name==rhizome_type()||name=="Thing";
        }

        Thing *
        Parser::clone() const {
            Parser *c = new Parser();
            
            return c;
        }

        Thing *
        Parser::invoke( string const &method, Thing *arg ) {
            (void)method; (void)arg;
            throw runtime_error("invoke: implement me!");
        }

        void
        Parser::dump( std::ostream &out ) const {
            out << "DEBUG DUMP: parser\n";
            out << "==================\n";
            out << "Rules:\n";
            rules.dump(out);
        }



        Gramex * lit(string const &w) {
            return new Literal(w);
        }

        Gramex * seq(Gramex *a, Gramex *b) {
            And *p = new And();
            p->append(a);
            p->append(b);
            return p;
        }

        Gramex * seq(Gramex *a, Gramex *b, Gramex *c) {
            And *p = new And();
            p->append(a);
            p->append(b);
            p->append(c);
            return p;
        }
        Gramex * seq(Gramex *a, Gramex *b, Gramex *c, Gramex *d) {
            And *p = new And();
            p->append(a);
            p->append(b);
            p->append(c);
            p->append(d);
            return p;
        }

        Gramex * options( std::vector<Gramex *> cs ) {
            Or *p = new Or();
            for( auto i=cs.begin(); i!=cs.end(); ++i) {
                p->add_clause( *i );
            }
            return p;
        }

        Gramex * non_term(string const &name) {
            return new NonTerminal(name);
        }

        Gramex * match_type( string const &tname ) {
            return new MatchType(tname);
        }

        Gramex * plus( Gramex *inner ) {
            return new PlusClosure(inner);
        }

        Gramex * star( Gramex *inner ) {
            return new StarClosure(inner);
        }

        Gramex * parens( Gramex *inner ) {
            And *n = new And();
            n->append( lit("("));
            n->append(inner);
            n->append( lit(")"));
            return n;
        }

        Gramex * comma_list( std::vector<Gramex*> elems, string sep ) {
            And *n = new And();
            for(size_t i=0; i<elems.size(); ++i) {
                n->append( elems[i]);
                if( i < elems.size()-1 ) {
                    n->append(lit(sep));
                }
            }
            return n;
        }

        Gramex * apply( Gramex *inner, TransformFn f ) {
            Transform *t = new Transform( inner, f );
            return t;
        }
    }
}