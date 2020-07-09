#include "table.hpp"

using rhizome::core::indent;

namespace rhizome {
    namespace types {
        Table::Table() {

        }

        string Table::rhizome_type() const {
            return "Table";
        }

        

        void Table::serialize_to( size_t level, ostream &out ) const {
            out << indent( level) << "Table {\n";
            for( auto row = rows.begin(); row != rows.end(); row++) {
                out << indent(level+1) << row->first << ":";
                row->second->serialize_to(level+2, out);
                auto whu = row;
                if( ++whu != rows.end() ) {
                    out << ",";
                }
            }
            out << indent(level) << "}\n";
        }

        bool Table::contains( string const &name ) const {
            return rows.count(name) > 0;
        }

        void Table::remove( string const &name ) {
            if( rows.count(name) > 0 ) {
                delete rows[name];
                rows.erase(name);
            }
        }

        Thing * Table::get( string const &name ) {
            if( rows.count(name)) {
                return rows.at(name);
            } else {
                throw runtime_error("No such record.");
            }
        }

        void Table::set( string const &name, Thing *thing ) {
            remove(name);
            rows[name] = thing;
        }

        Thing * Table::clone() const {
            Table *copy = new Table();
            for( auto i=rows.begin(); i!=rows.end(); i++) {
                copy->set( i->first, i->second->clone() );
            }
            return copy;
        }

        bool
        Table::has_interface(string const &w) {
            return (w==rhizome_type()||w=="Thing");
        }

        Thing *
        Table::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)method;(void)arg; (void)context;
            throw runtime_error("Nothing to invoke.");
        }

    }
}