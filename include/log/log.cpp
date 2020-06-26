#include "log.hpp"

namespace rhizome {
    namespace log {
        string red( string const &m ) {
            stringstream ss;
            ss << rhizome::ui::FG_RED_ON << m << rhizome::ui::RESET_COLOR;
            return ss.str();
        }

        string green( string const &m ) {
            stringstream ss;
            ss << rhizome::ui::FG_GREEN_ON << m << rhizome::ui::RESET_COLOR;
            return ss.str();
        }

        string yellow( string const &m ) {
            stringstream ss;
            ss << rhizome::ui::FG_YELLOW_ON << m << rhizome::ui::RESET_COLOR;
            return ss.str();
        }

        string cyan( string const &m ) {
            stringstream ss;
            ss << rhizome::ui::FG_CYAN_ON << m << rhizome::ui::RESET_COLOR;
            return ss.str();
        }

        string cat( string const &s0, string const &s1 ) {
            stringstream ss;
            ss << s0 << s1;
            return ss.str();
        }

        string cat( string const &s0, string const &s1, string const &s2 ) {
            stringstream ss;
            ss << s0 << s1 << s2;
            return ss.str();
        }

        string when( string const &m ) {
            rhizome::types::Time ts;
            stringstream ss;
            ss << ts << " " << m;
            return ss.str();
        }

        string logfilename( string const &section ) {
            rhizome::types::Time t;
            stringstream fn;
            fn << "log/" << section << "_" << t.year() << "-" << t.month() << "-" << t.day() << ".log";
            return fn.str();
        }

        Log::Log(string const &section, bool echo): section(section), echo(echo), max_ents(20), min_ents(10) {

        }

        Log::~Log() {
            if( messages.size() > 0) {
                ofstream logfile;
                logfile.open( logfilename(section), std::fstream::app | std::fstream::out );
                while( messages.size() > 0 ) {
                    logfile << messages.front() << std::endl;
                    messages.pop_front();
                }
                logfile.close();
            }
        }

        void
        Log::log( string const &msg ) {
            messages.push_back(msg);
            if( messages.size() >= max_ents ) {
                ofstream logfile;
                logfile.open( logfilename(section), std::fstream::app | std::fstream::out );
                while( messages.size() > min_ents ) {
                    logfile << messages.front() << std::endl;
                    messages.pop_front();
                }
                logfile.close();
            }
        }

        void
        Log::info( string const &msg ) {
            
            string m = when(cat(green(cat(section,":[Info] ")),msg));
            log(m);
            if( echo ) {
                std::cout << m << std::endl;
            }
        }

        void
        Log::warn( string const &msg ) {
            string m = when(cat(yellow(rhizome::ui::warning),msg));
            log(m);
            if( echo ) {
                std::cout << m << std::endl;
            }
        }

        void
        Log::error( string const &msg ) {
            string m = when(cat(red("[Error] "),msg));
            log(m);
            if(echo) {
                std::cout << m << std::endl;
            }
            throw std::runtime_error(m);
        }

        void
        Log::debug( string const &msg ) {
            string m = when(cat(cyan("[Debug] "),msg));
            log(m);
            if(echo) {
                std::cout << m << std::endl;
            }
        }


    }
}