#ifndef RHIZOME_UI_CHESS_BOARD_HPP
#define RHIZOME_UI_CHESS_BOARD_HPP
#include <map>
#include <locale>
#include <codecvt>
#include <string>
#include <cwchar>
#include <vector>
#include <sstream>
#include <cassert>
#include <tuple>
#include "ui.hpp"
#include "console.hpp"
#include "core/thing.hpp"
using std::wstring;
using std::vector;
using std::map;
using std::stringstream;
using std::pair;
using rhizome::core::Thing;

namespace rhizome {
    namespace ui {
        
        

        class ChessBoard: public Thing {
        private:
            vector< vector<string> > board;
            size_t x; size_t y;
            size_t width; size_t height;
            int to_play;
        public:
            ChessBoard( size_t x, size_t y, size_t width, size_t height );
            

            string row( size_t row_number ) const;
            void display( Console &console ) const;

            void place( size_t row, size_t col, string const &piece );
            void set_row( size_t row_number, vector<string> const &row );
            
            // board size.
            size_t Height() const;
            size_t Width() const;

            // thing interface
            string rhizome_type() const override;
            bool has_interface( string const &name ) override;
            void serialize_to(size_t level, std::ostream &out) const override;
            Thing * clone() const override;
            Thing * invoke( Thing *context, string const &method, Thing *arg ) override;
            
            bool move( string const &from, string const &to );
        };

        namespace chess {

            static const string BLACK_PAWN = "\033[1;32m♟︎";
            static const string BLACK_KING = "\033[1;32m♚";
            static const string WHITE_KING = "\033[1;34m♚";
            static const string WHITE_QUEEN = "\033[1;34m♛";
            static const string BLACK_QUEEN = "\033[1;32m♛";
            static const string WHITE_ROOK = "\033[1;34m♜";
            static const string BLACK_ROOK = "\033[1;32m♜";
            static const string WHITE_BISHOP = "\033[1;34m♝";
            static const string BLACK_BISHOP = "\033[1;32m♝";
            static const string WHITE_KNIGHT = "\033[1;34m♞";
            static const string BLACK_KNIGHT = "\033[1;32m♞";
                
            static const string WHITE_PAWN = "\033[1;34m♟︎";
            static const string EMPTY = " ";
            static const int BLACK = 1;
            static const int WHITE = 0;
            // bidirectional map-ish
            static const map<string,string> SERIALIZE_MAP = {
                {BLACK_PAWN,   "♟︎"},
                {BLACK_KING,   "♚"},
                {BLACK_QUEEN,  "♛"},
                {BLACK_ROOK,   "♜"},
                {BLACK_BISHOP, "♝"},
                {BLACK_KNIGHT, "♞"},

                {WHITE_KING,   "♔"},
                {WHITE_QUEEN,  "♕"},
                {WHITE_ROOK,   "♖"},
                {WHITE_BISHOP, "♗"},
                {WHITE_KNIGHT, "♘"},
                {WHITE_PAWN,   "♙"},

                {"♟︎",BLACK_PAWN},
                {"♚",BLACK_KING},
                {"♛",BLACK_QUEEN},
                {"♜",BLACK_ROOK},
                {"♝",BLACK_BISHOP},
                {"♞",BLACK_KNIGHT},

                {"♔",WHITE_KING},
                {"♕",WHITE_QUEEN},
                {"♖",WHITE_ROOK},
                {"♗",WHITE_BISHOP},
                {"♘",WHITE_KNIGHT},
                {"♙",WHITE_PAWN},

                {EMPTY,EMPTY}
            };

            static const vector<string> STANDARD_SETUP_BLACK = {
                BLACK_ROOK, 
                BLACK_BISHOP, 
                BLACK_KNIGHT, 
                BLACK_QUEEN, 
                BLACK_KING, 
                BLACK_BISHOP, 
                BLACK_KNIGHT, 
                BLACK_ROOK
            };

            static const vector<string> STANDARD_SETUP_WHITE = {
                WHITE_ROOK,
                WHITE_BISHOP,
                WHITE_KNIGHT,
                WHITE_QUEEN,
                WHITE_KING,
                WHITE_BISHOP,
                WHITE_KNIGHT,
                WHITE_ROOK
            };

            vector<string> row_of( string const &piece, size_t width );
            

            void clear( ChessBoard *b );
            void standard_setup( ChessBoard *b );
            void fischer_setup( ChessBoard *b );
            
            // go from algebraic coordinates to array indeces.
            pair<size_t,size_t> coord(string const &algebraic);
            
            
        }
    }
}

#endif