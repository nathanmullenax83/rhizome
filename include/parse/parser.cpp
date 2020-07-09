#include <cassert>
#include "parser.hpp"

#include "log/log.hpp"
#include "types/binary_expression.hpp"

using rhizome::types::BinaryExpression;

namespace rhizome {
    namespace parse {
        Pattern *
        decimal_pattern() {
            pat::Cat *c = new pat::Cat();
            c->append( new pat::Plus( new pat::Digit() ));
            c->append( new pat::Literal("."));
            c->append( new pat::Plus( new pat::Digit() ));
            return c;
        }

        Pattern *
        integer_pattern() { 
            pat::Plus *p = pat::plus( new pat::Digit() );

            return pat::cat({
                pat::maybe(pat::p_literal("-")),
                p
            });
        }

        Pattern *
        string_pattern() {
            pat::Cat *c = new pat::Cat();
            c->append(pat::p_literal("\""));
            c->append(new pat::Star( new pat::Negated(new pat::Chars("\""))));
            c->append( pat::p_literal("\""));
            return c;
        }

        Parser::Parser(Lexer *lexer): lexer(lexer) {
            
        }

        Parser::~Parser() {
            delete lexer;
        }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
        Parser::Parser() {
            static rhizome::log::Log log("parser_constructor");
            auto &cap = log;
            lexer = new Lexer();
            
            lexer->define_token_type( "Newline", new pat::Transform( new pat::Literal("\n"),[](Thing *t){
                return t;
            }));
            lexer->define_token_type( "Whitespace", new pat::Transform( new pat::Plus(new pat::Or(new pat::Literal(" "),new pat::Literal("\t"))),
                []( Thing *t ){
                    delete t;
                    return (Thing*)NULL;
                }));

            lexer->define_token_type( "Bool", new pat::Transform(
                new pat::Or( new pat::Literal("true"), new pat::Literal("false")),
                [] (Thing *t){
                    string v = ((String*)t)->native_string();
                    rhizome::types::Bool *b = new rhizome::types::Bool(v=="true");
                    return b;
                }
            ));
            
            lexer->define_token_type( "Decimal", new pat::Transform( decimal_pattern(),
                [&cap]( Thing *t ) {
                    //cap.info("Matched Decimal pattern.");
                    assert(t!=NULL && t->rhizome_type()=="String");
                    //cap.info("Token type is string:");
                    string v = ((String*)t)->native_string();
                    //cap.info(v);
                    delete t;
                    //cap.info("Deleted t");
                    rhizome::types::Float *f = new rhizome::types::Float(v);
                    stringstream eff;
                    f->serialize_to(0,eff);
                    //cap.info(eff.str());
                    return f;
                }));
            lexer->define_token_type( "Int", new pat::Transform( integer_pattern(),
                []( Thing *t ) {
                    string v = ((String*)t)->native_string();
                    delete t;
                    return new rhizome::types::Integer(v);
                }));
            lexer->define_token_type( "String", new pat::Transform( string_pattern(),
                [&cap]( Thing *t )     {
                    //cap.info("Lexer 'String' rule matched.");
                    assert( t!=NULL );
                    assert( t->rhizome_type()=="String");

                    string v = ((String*)t)->native_string();
                    //cap.info("Contents of token: ");
                    //cap.info(v.c_str());

                    delete t;
                    return new rhizome::types::String(v);
                }));
            
            lexer->define_token_type( "OParen", "(");
            lexer->define_token_type( "CParen", ")");
            lexer->define_token_type( "OBrack", "{");
            lexer->define_token_type( "CBrack", "}");
            lexer->define_token_type( "Comma", ",");
            lexer->define_token_type( "Colon", ":");
            lexer->define_token_type( "Semicolon", ";");
            lexer->define_token_type( "Plus", "+");
            lexer->define_token_type( "Minus", "-");
            lexer->define_token_type( "Carat", "^");
            lexer->define_token_type( "Times", "*");
            lexer->define_token_type( "Div", "/");
            lexer->define_token_type( "Dot", ".");
            lexer->define_token_type( "Equals","=");
            lexer->define_token_type( "LT", "<");
            lexer->define_token_type( "GT", ">");
            lexer->define_token_type( "Bareword",
                    new pat::Cat(
                        new pat::Plus( new pat::Alpha() ),
                        new pat::Star( new pat::Or( new pat::Alpha(), new pat::Digit() ))
                    )
                );
        }
#pragma GCC diagnostic pop
        ILexer * Parser::get_lexer() {
            return lexer;
        }

        void Parser::clear() {
            lexer->clear();
        }

        void
        Parser::rule( string const &w, Gramex *g ) {
            rules.rule(w,g);
        }

        IGramex *
        Parser::lookup( string const &name ) const {
            return rules.lookup(name);
        }

        Thing *
        Parser::parse_thing( string const &start_rule ) {
            
            IGramex *start = lookup(start_rule);
#ifdef INSTRUMENTED
            std::cout << "-- Start rule: [Parser::parse_thing]\n";
            ((Gramex*)start)->serialize_to(std::cout);
            std::cout << "\n";
#endif
            
            GrammarFn static_lookup = [this]( string const &name ) { return this->lookup(name);};
            stringstream captured;
            start->match( lexer, static_lookup, captured );

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
#ifdef INSTRUMENTED
            std::cout << "-- parsed thing [Parser::parse_thing].\n";
#endif
        }

        Thing *
        Parser::parse_thing( string const &start, string const &thing ) {
            stringstream ss;
            ss << thing;
            q_stream(ss);
            return parse_thing(start);
        }

        void
        Parser::q_stream( istream &in ) {
            lexer->q(in);
        }

        void
        Parser::serialize_to( size_t level, std::ostream &out ) const {
            (void)level;
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
        Parser::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)method; (void)arg; (void)context;
            throw runtime_error("invoke: implement me!");
        }

        void
        Parser::dump( std::ostream &out ) const {
            out << "\n";
            rules.dump(out);
        }

        Gramex * gx_literal(string const &w) {
            return new Literal(w);
        }

        Gramex * gx_sequence( vector<Gramex*> ps ) {
            And *p = new And();
            for( auto i = ps.begin(); i!=ps.end(); i++ ) {
                p->append(*i);
            }
            return p;
        }

        Gramex * gx_options( std::vector<Gramex *> cs ) {
            Or *p = new Or();
            for( auto i=cs.begin(); i!=cs.end(); ++i) {
                p->add_clause( *i );
            }
            return p;
        }

        Gramex * gx_options( std::vector<string> cs ) {
            if( cs.size() > 1 ) {
                Or *p = new Or();
                for( auto i=cs.begin(); i!=cs.end(); i++) {
                    p->add_clause(gx_literal(*i));
                }
                return p;
            } else {
                assert(cs.size()==1);
                return gx_literal(cs[0]);
            }
        }

        Gramex * gx_non_terminal(string const &name) {
            return new NonTerminal(name);
        }

        Gramex * gx_match_type( string const &tname ) {
            return new MatchType(tname);
        }

        Gramex * gx_match_lexer_rule( string const &name ) {
            return new MatchRule(name);
        }

        Gramex * gx_plus_closure( Gramex *inner ) {
            return new PlusClosure(inner);
        }

        Gramex * gx_star_closure( Gramex *inner ) {
            return new StarClosure(inner);
        }

        

        Gramex * gx_apply( Gramex *inner, TransformFn f ) {
            Transform *t = new Transform( inner, f );
            return t;
        }

        Gramex * gx_maybe( Gramex *inner ) {
            MaybeClosure *mb = new MaybeClosure(inner);
            return mb;
        }

        Gramex * gx_parens( Gramex *inner ) {
            return gx_sequence({
                gx_literal("("),
                inner,
                gx_literal(")")
            });
        }

        Gramex * gx_comma_list( std::vector<Gramex*> elems, string sep ) {
            And *n = new And();
            for(size_t i=0; i<elems.size(); ++i) {
                n->append( elems[i]);
                if( i < elems.size()-1 ) {
                    n->append(gx_literal(sep));
                }
            }
            return n;
        }

        Gramex * gx_binary_infix_operator_left( vector<string> ops, string const &subex ) {
            Gramex *list = 
                gx_apply(
                    gx_sequence({
                        gx_star_closure(
                            gx_sequence({
                                gx_non_terminal(subex),
                                gx_options(ops)
                            })
                        ),
                        gx_non_terminal(subex)
                    }),
                    []( deque<Thing*> ts ) {
                        if( ts.size()==1) {
                            return ts[0];
                        } else {
                            Expression *left = (Expression*)ts[0];
                            BinaryExpression *be;
                            for(size_t i=1; i<ts.size(); i+=2) {
                                String *op = (String*)(ts[i]);
                                Expression *right = (Expression*)ts[i+1];
                                be = new BinaryExpression(op->native_string(),left,right);
                                left = be;
                            }
                            return (Thing*)be;
                        }
                        
                    }
                );
            return list;
        }

        Gramex * gx_binary_infix_operator_right( vector<string> ops, string const &subex ) {
            Gramex *list = 
                gx_apply(
                    gx_sequence({
                        gx_star_closure(
                            gx_sequence({
                                gx_non_terminal(subex),
                                gx_options(ops)
                            })
                        ),
                        gx_non_terminal(subex)
                    }),
                    []( deque<Thing*> ts ) {
                        if( ts.size()==1) {
                            return ts[0];
                        } else {
                            Expression *right = (Expression*)ts[ts.size()-1];
                            BinaryExpression *be;
                            for(size_t i=ts.size()-2; i>0; i-=2) {
                                String *op = (String*)(ts[i]);
                                Expression *left = (Expression*)ts[i-1];
                                be = new BinaryExpression(op->native_string(),left,right);
                                right = be;
                            }
                            return (Thing*)be;
                        }
                        
                    }
                );
            return list;
        }
    }
}