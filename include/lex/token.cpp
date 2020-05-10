#include "token.hpp"

namespace rhizome {
    namespace lex {
        Token::Token(): tvalue(""), tname("") {

        }

        Token::Token( string const &tvalue, string const &tname )
        : tvalue(tvalue), tname(tname) {

        }

        Token::~Token() {

        }

        void Token::set( string const &value, string const &name, size_t line, size_t col ) {
            tvalue = value;
            tname = name;
            line_no = line;
            col_no = col;
        }

        ostream & operator << ( ostream &out, Token const &t ) {
            out << "'" << t.token_value() << "'" << " [" << t.token_class() << "]";
            return out;
        }

        size_t 
        Token::line() const { return line_no; }

        size_t
        Token::column() const { return col_no; }

        string
        Token::token_value() const { return tvalue; }

        string
        Token::token_class() const { return tname; }

        void
        Token::serialize_to( ostream &out ) const {
            out << "Token(";
            out << tvalue << "," << tvalue;
            out << "," << line() << "," << column();
            out << ")";
        }

        Thing *
        Token::clone() const {
            Token *t2 = new Token();
            t2->set( token_value(), token_class(), line(), column() );
            return t2;
        }

        

        string
        Token::rhizome_type() const {
            return "Token";
        }

        bool
        Token::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Thing";
        }

        Thing *
        Token::invoke( string const &method, Thing *arg ) {
            (void)method;(void)arg;
            throw runtime_error("Nothing to invoke.");
        }
    }
}