#ifndef RHIZOME_LEX_TOKEN_HPP
#define RHIZOME_LEX_TOKEN_HPP

#include <string>
#include <iostream>
#include <stdexcept>
#include "core/thing.hpp"
#include "core/i_token.hpp"

using std::string;
using std::ostream;
using std::runtime_error;

using rhizome::core::Thing;
using rhizome::core::IToken;

namespace rhizome {
    namespace lex {
        class Token: public Thing, public IToken {
        public:
            /// String representation.
            string tvalue;
            string tname;
            size_t line_no;
            size_t col_no;

            /// Create an 'empty' token.
            Token();
            virtual ~Token();

            /// Create a token with a specified initial value and type.
            /// @param{value} Token value.
            /// @param{type} Numeric type ID.
            Token( string const &tvalue, string const &tname );

            virtual void set( string const &value, string const &tname, size_t line_no, size_t col ) override;
            virtual size_t line() const override;
            virtual size_t column() const override;

            virtual string token_value() const override;
            virtual string token_class() const override;

            // Thing::type()
            virtual string rhizome_type() const override;

            virtual void serialize_to( ostream &out ) const override;
            virtual Thing * clone() const override;
            
            
            virtual bool has_interface( string const &name ) override;
            virtual Thing * invoke( string const &method, Thing *arg ) override;
        };

        ostream & operator << ( ostream &out, Token const &t );
    }
}

#endif
