#ifndef RHIZOME_ENDUSER_HPP
#define RHIZOME_ENDUSER_HPP

/* This file contains everything to construct a system using rhizome. It should 
   be the only include you need. */

#include "core/thing.hpp"
#include "core/i_parser.hpp"
#include "core/i_store.hpp"
#include "core/system.hpp"
#include "core/universe.hpp"
#include "alphabet.hpp"
#include "words.hpp"
#include "lex.hpp"
#include "pattern.hpp"
#include "parse.hpp"
#include "types.hpp"
#include "store.hpp"
#include "html.hpp"
#include "net.hpp"
#include "sdt.hpp"

namespace rhizome {
    IParser *create_lexer_grammar();

    IParser *create_rhizome_parser();

    ILexer *load_lexer( string const &filename );
    // system check
    bool verify();

    /// Convert to native boolean. Will throw runtime_error if cast is invalid.
    bool system_bool( Thing *t );

    /// Turn anything into a string
    string to_system_string( Thing *t );

    /// Extract an arbitrary precision integer, if applicable, throw a runtime_error otherwise.
    mpz_class system_mpz( Thing *t );

    /// Extract a long double value from int,float,fraction
    long double system_float( Thing *t );

    /// Widen a string, apply mapping, then convert back to UTF8
    /// This is good for console effects, like alternative fonts.
    string apply_mapping( string s, rhizome::alphabet::Mapping &m);
}


#endif
