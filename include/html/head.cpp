#include "head.hpp"

namespace rhizome {
    namespace html {
        Head::Head() {

        }

        Head::~Head() {

        }

        void
        Head::write_to( ostream &out, size_t indent ) const {
            string spacer( indent*4,' ' );
            out << spacer << "<head>\n";
            write_children(out, indent+1);
            out << spacer << "</head>\n";
        }

        Title &
        Head::title( string const &t ) {
            Title *title = new Title(t);
            add_child(title);
            return *title;
        }

        void
        Head::serialize_to( size_t level, ostream &out ) const {
            write_to(out,level);
        }

        Thing *
        Head::clone() const {
            Head *h = new Head();
            h->children = clone_children();
            return h;
        }

        string
        Head::rhizome_type() const {
            return "html::Head";
        }

        bool
        Head::has_interface( string const &name ) {
            return (name==rhizome_type()||name=="Thing");
        }

        Thing *
        Head::invoke( Thing *context, string const &name, Thing *arg ) {
            (void)arg; (void)context;
            stringstream ss;
            ss << "No such method: " << name;
            throw runtime_error(ss.str());
        }
    }
}