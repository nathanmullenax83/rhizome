#include "dir.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdexcept>
#include <sstream>
#include <dirent.h>


#include "types/tuple.hpp"
#include "types/string.hpp"

using std::runtime_error;
using std::stringstream;

using rhizome::core::Dispatcher;
using rhizome::core::indent;
using rhizome::types::Tuple;
using rhizome::types::String;

namespace rhizome {
    namespace types {

        namespace dir {
            static Dispatcher<Dir> dispatcher({
                {
                    "files",[] ( Thing *context, Dir *that, Thing *arg ) {
                        (void)context;
                        vector<string> fs;
                        // Function is overloaded file() is all files and files /pattern/ is filtered.
                        if( arg!= NULL ) {
                            assert( arg->has_interface("pattern"));
                            Pattern *p = (Pattern*)arg;
                            fs = that->files(p);
                        } else {
                            fs = that->files(NULL);
                        }
                        Tuple *the_files = new Tuple();
                        for(size_t i=0; i<fs.size(); ++i) {
                            the_files->append(new String(fs[i]));
                        }
                        return the_files;
                    }
                }
            });
        }

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
        Dir::serialize_to( size_t level, std::ostream &out ) const {
            out << indent(level) << rhizome_type() << " (\n";
            out << indent(level+1) << path;
            out << indent(level) << ")\n";
        }

        Thing *
        Dir::invoke( Thing *context, string const &method, Thing *arg ) {
            
            try {
                Thing *r = dir::dispatcher.at(method)(context,this,arg);
                return r;
            } catch( std::exception *e ) {
                stringstream err;
                err << "Method " << method << " could not be invoked on " << rhizome_type() << ".\n";
                if( context != NULL ) {
                    err << "Context:\n    ";
                    context->serialize_to(1,err);
                }
                throw runtime_error(err.str());
            }
            
            
            
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