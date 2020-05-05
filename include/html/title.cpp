#include "title.hpp"

namespace rhizome {
    namespace html {
        Title::Title(): cdata("") {

        }

        Title::Title( string const &cdata ): cdata(cdata) {

        }

        Title::~Title() {

        }

        void
        Title::write_to( ostream &out ) {
            out << "<title>";
            out << cdata;
            out << "</title>";
        }

        void
        Title::serialize_to( ostream &out ) const {
            out << rhizome_type() << "(\"";
            out << cdata;
            out << "\")";
        }

        // void
        // Title::deserialize_from( istream &in, IParser *parser ) {
        //     parser->match_literal(in,"title");
        //     parser->match_literal(in,"(");
        //     cdata = parser->match_qstring(in);
        //     parser->match_literal(in,")");
        // }

        // rp::Pattern *
        // Title::make_pattern() const {
        //     return NULL;
        // }

        // rp::Pattern *
        // Title::make_concise_pattern() const {
        //     return NULL;
        // }

        Thing * 
        Title::clone() const {
            return new Title(cdata);
        }

        string
        Title::rhizome_type() const {
            return "html::Title";
        }
    }
}