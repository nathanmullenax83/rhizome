#include "head.hpp"

namespace rhizome {
    namespace html {
        Head::Head() {

        }

        Head::~Head() {

        }

        void
        Head::write_to( ostream &out ) {
            out << "\t<head>\n";
            write_children(out);
            out << "\t</head>\n";
        }

        Title &
        Head::title( string const &t ) {
            Title *title = new Title(t);
            add_child(title);
            return *title;
        }

        void
        Head::serialize_to( ostream &out ) const {
            out << rhizome_type() << "(";
            serialize_children(out);
            out << ")";
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
        Head::invoke( string const &name, Thing *arg ) {
            (void)arg;
            stringstream ss;
            ss << "No such method: " << name;
            throw runtime_error(ss.str());
        }
    }
}