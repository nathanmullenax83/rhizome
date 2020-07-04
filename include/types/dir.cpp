#include "dir.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdexcept>
#include <sstream>
#include <dirent.h>



using std::runtime_error;
using std::stringstream;

namespace rhizome {
    namespace types {
        bool
        Dir::dir_exists( string const &name ) {
            struct stat st{};
            return stat( name.c_str(), &st )==0;
        }

        bool
        Dir::dir_create( string const &name ) {
            if( mkdir(name.c_str(), 0700)==0 ) {
                return true;
            } else {
                throw runtime_error("Coudln't create directory.");
            }
        }


        string
        Dir::prefix() const {
            return path;
        }


        Dir::Dir(): path(".") {

        }

        Dir::Dir( string const &name ): path(name) {
            if( !dir_exists(name)) {
                dir_create(name);
            }
        }

        string
        Dir::rhizome_type() const {
            return "Dir";
        }

        Thing *
        Dir::clone() const {
            Dir *copy = new Dir(this->path);
            return copy;
        }

        bool
        Dir::has_interface( string const &name ) {
            return name==rhizome_type()||name=="Thing";
        }

        void
        Dir::serialize_to( std::ostream &out ) const {
            out << rhizome_type() << "(";
            out << path;
            out << ")";
        }

        Thing *
        Dir::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)method; (void)arg; (void)context;
            throw runtime_error("Invoke failed.");
        }

        vector<string>
        Dir::files( Pattern *filter ) {
            vector<string> fs;
            DIR *dir = opendir(prefix().c_str());
            errno = 0;
            while(dir) {
                dirent *dp;
                if ((dp = readdir(dir)) != NULL) {
                    if( filter->accepts(string(dp->d_name)) ) {
                        fs.push_back( string(dp->d_name));
                    }
                } else {
                    closedir(dir);
                }

            }
            return fs;
        }
    }
}