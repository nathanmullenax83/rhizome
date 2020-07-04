#include "thead.hpp"

namespace rhizome {
    namespace html {
        THead::THead() {

        }

        THead::~THead() {

        }

        void
        THead::write_to( ostream &out, size_t indent ) {
            string spacer(indent*4,' ');
            out << spacer << "<thead>";
            row.write_to(out,indent+1);
            out << spacer << "</thead>";
        }

        void
        THead::serialize_to( ostream &out ) const {
            out << "thead(";
            row.serialize_to(out);
            out << ")";
        }

        // void
        // THead::deserialize_from( istream &in, IParser *parser ) {
        //     parser->match_literal(in,"thead");
        //     parser->match_literal(in,"(");
        //     parser->match_literal(in,")");
        // }

        void
        THead::add_column(string const &name) {
            Th *header = new Th(name,"col");
            add_child(header);
        }

        Thing * 
        THead::clone() const {
            THead *thead = new THead();
            thead->children = clone_children();
            return thead;
        }

        // rp::Pattern *
        // THead::make_pattern() const {
        //     return NULL;
        // }

        // rp::Pattern *
        // THead::make_concise_pattern() const {
        //     return NULL;
        // }

        string
        THead::rhizome_type() const {
            return "html::THead";
        }

        Thing *
        THead::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)context; (void)method; (void)arg;
            throw runtime_error("Not implemented.");
        }
    }
}