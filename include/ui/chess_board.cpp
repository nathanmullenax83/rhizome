#include "chess_board.hpp"

namespace rhizome {
    namespace ui {
        namespace chess {
            vector<string> row_of( string const &piece, size_t width ) {
                return vector<string>(width,piece);
            }

            void standard_setup(ChessBoard *b) {
                size_t height = b->Height();
                size_t width = b->Width();
                assert(width==8);
                b->set_row(0,STANDARD_SETUP_BLACK);
                b->set_row(1,row_of(BLACK_PAWN,width));
                for(size_t i=2; i<height-2; ++i) {
                    b->set_row(i,row_of(EMPTY,width));
                }
                b->set_row(height-2,row_of(WHITE_PAWN,width));
                b->set_row(height-1,STANDARD_SETUP_WHITE);
            }

            pair<size_t,size_t> coord( string const &algebraic ) {
                char letter = algebraic[0];
                char numeral = algebraic[1];
                pair<size_t,size_t> p(numeral-'0', letter - (std::isupper(letter)?'A':'a'));
                return p;
            }
        }

        size_t
        ChessBoard::Width() const {
            return width;
        }

        size_t
        ChessBoard::Height() const {
            return height;
        }

        ChessBoard::ChessBoard(size_t x, size_t y, size_t width, size_t height) 
        : x(x), y(y), width(width), height(height) {
            vector<string> row;
            for(size_t i=0; i<height; ++i) {
                board.push_back(chess::row_of(chess::EMPTY,width));
            }
            if( width==8) {
                chess::standard_setup(this);
            }
            to_play = rand()%2;
        }

        bool white( int x, int y ) {
            return (x%2) != (y%2);
        }

        string
        ChessBoard::row( size_t row_number ) const {
            //auto &conv = console.get_converter();
            stringstream r;
            assert(row_number < board.size());
            auto &Row = board[row_number];
            for(size_t i=0; i<Row.size(); ++i) {
                r << (white(i,row_number)?BG_WHITE_ON:BG_BLACK_ON);
                r << FG_WHITE_ON;
                r << " ";
                r << Row[i];
                r << " ";
                r << RESET_COLOR;
            }
            return r.str();
        }

        void
        ChessBoard::place( size_t row, size_t col, string const &piece ) {
            assert( (row < height) && (col < width) );
            board[row][col] = piece;
        }
        
        void
        ChessBoard::set_row( size_t row_number, vector<string> const &the_row ) {
            assert( the_row.size()==width );
            assert( row_number < height );
            board[row_number] = the_row;
        }
        

        void
        ChessBoard::display( Console &console ) const {
            static const string alphabet = "abcdefghijklmnopqrstuvwxyz";
            for( size_t i=0; i<width; ++i) {
                console.locate(3*(x+i),y);
                console.putch(alphabet[i]);
            }
            for( size_t y=0; y<height; ++y) {
                console.locate(x,y+this->y+1);
                size_t row_index = height - y;
                if( row_index < 10 ) {
                    console << " " << row_index << " ";
                } else {
                    console << row_index << " ";
                }
                
                console << row(y);
            }
        }

        // thing implementation
        string
        ChessBoard::rhizome_type() const {
            return "ChessBoard";
        }

        bool
        ChessBoard::has_interface( string const &name ) {
            return name=="Thing"||name==rhizome_type();
        }

        Thing *
        ChessBoard::clone() const {
            ChessBoard *cb = new ChessBoard(x,y,width,height);
            cb->board = board;
            cb->to_play = to_play;
            return cb;
        }

        string unrecognized_method( string const &name, Thing *arg ) {
            stringstream err;
            err << "Method " << name << " is unrecognized by the ChessBoard class. Argument was ";
            arg->serialize_to(err);
            err << ".";
            return err.str();
        }

        Thing * 
        ChessBoard::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)context;
            if( method=="clone" && arg==NULL ) {
                return clone();
            }
            throw runtime_error(unrecognized_method(method,arg));
        }

        void
        ChessBoard::serialize_to( std::ostream &out ) const {
            out << rhizome_type() << "{\n";
            for( size_t y=0; y<height; ++y) {
                out << "\t\"";
                for( size_t x=0; x<width; ++x) {
                    out << chess::SERIALIZE_MAP.at(board[y][x]);
                }
                out << "\"\n";
            }
            out << "}\n";
        }
    }
}