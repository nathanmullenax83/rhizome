#include "time.hpp"

// note: this isn't thread-safe. localtime
// returns a pointer to a shared object.

#include <string>
#include <sstream>
#include <cassert>

using std::stringstream;
using std::string;


namespace rhizome {
    namespace types {
        Time::Time() {
            t = time(NULL);
        }

        Time::Time( int year, int month, int day ) {
            assert(year>=0);
            assert(month>=0);
            assert(day>=0);
            struct tm the_tm;
            the_tm.tm_year = year-1900;
            the_tm.tm_mon = month%12;
            the_tm.tm_mday = day;
            the_tm.tm_sec = 0;
            the_tm.tm_hour = 0;
            the_tm.tm_min = 0;
            t = mktime(&the_tm);
        }

        int
        Time::year() const {
            struct tm * lt;
            lt = std::localtime(&t);
            // tm_year stores years since 1900...
            return 1900 + lt->tm_year;
        }

        int 
        Time::month() const {
            struct tm * lt;
            lt = std::localtime(&t);
            return lt->tm_mon;
        }

        int
        Time::day()  const {
            struct tm * lt;
            lt = std::localtime(&t);
            return lt->tm_mday;
        }

        int
        Time::hour() const {
            struct tm * lt;
            lt = std::localtime(&t);
            return lt->tm_hour;
        }

        int
        Time::minute() const {
            struct tm * lt;
            lt = std::localtime(&t);
            return lt->tm_min;
        }

        int
        Time::second() const {
            struct tm * lt;
            lt = std::localtime(&t);
            return lt->tm_sec;
        }

        // why are we using a 'non-static dispatcher'?
        // the pattern is the same per type. Anticipating:
        // types themselves can be dynamically constructed,
        // and hence the corresponding patterns must be constructed
        // at runtime per object instance!

        void
        Time::serialize_to( ostream &out ) const {
            out << rhizome_type() << "(" << t << ")";
        }

        Thing * 
        Time::clone() const {
            Time *tm = new Time();
            tm->t = t;
            return tm;
        }

        string
        Time::rhizome_type() const {
            return "Time";
        }

        time_t
        Time::get() const {
            return t;
        }

        bool
        Time::has_interface( string const &name ) {
            return (name=="Thing"||name=="ITime");
        }


        ostream & operator << (ostream &out, Time const &t) {
            out << t.year() << "-" 
                << std::setfill('0') << std::setw(2) << t.month() << "/" 
                << std::setfill('0') << std::setw(2) << t.day()
                << "@" 
                    << std::setfill('0') << std::setw(2) << t.hour() << ":" 
                    << std::setfill('0') << std::setw(2) << t.minute() << "." 
                    << std::setfill('0') << std::setw(2) << t.second();
            return out;            
        }
        Thing *
        Time::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)method;(void)arg; (void)context;
            throw runtime_error("Nothing to invoke.");
        }

        bool operator< ( Time const &a, Time const &b ) {
            return a.t < b.t;
        }
    }
}