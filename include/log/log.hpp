#ifndef RHIZOME_LOG_HPP
#define RHIZOME_LOG_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <string>
#include <deque>
#include <tuple>
#include <deque>
#include <map>
#include <stdexcept>
#include <cstdarg>
#include <cstdio>

#include "types.hpp"
#include "ui.hpp"

using std::deque;
using std::string;
using std::pair;
using std::deque;
using std::stringstream;
using std::ofstream;


namespace rhizome {
    namespace log {
        string red( string const &m );
        string green( string const &m );
        string cyan( string const &m );
        string yellow( string const &m );
        
        string cat( string const &s0, string const &s1 );
        string cat( string const &s0, 
                    string const &s1, 
                    string const &s2 );

        string when(string const &msg);

        /// Generate a filename for a log section.
        string logfilename( string const &section );

        class Log {
        private:
            string section;
            bool echo;
            size_t max_ents;
            size_t min_ents;
            deque<string> messages;
            

            void log( string const &s );
        public:
            Log(string const &section, bool echo=true);
            virtual ~Log();
            

            void debug( string const &msg);
            void info( string const &msg );
            void warn( string const &msg );
            void error( string const &msg);

        };
    }
}

#endif