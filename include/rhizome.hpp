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

    ILexer *load_lexer( string const &filename );
    // system check
    bool verify();
}


#endif
