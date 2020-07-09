#include "chars.hpp"
#include "types/string.hpp"

#include <string>
#include <locale>
#include <codecvt>

using rhizome::types::String;

namespace rhizome {
    namespace pattern {
        Chars::Chars(): state(0) {
            
        }

        Chars::Chars( string const &cees ): state(0) {
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            std::wstring ws = converter.from_bytes(cees);   

            for( size_t i=0; i<ws.size(); ++i) {
                cs.emplace( ws[i]);
            }
        }

        string Chars::rhizome_type() const {
            return "pattern::Chars";
        }

        bool Chars::has_interface( string const &w ) {
            return w==rhizome_type()||w=="Pattern"||w=="Thing";
        }

        void Chars::serialize_to( size_t level, std::ostream &out ) const {
            (void)level;
            //out << "{";
            for( auto i=cs.begin(); i!=cs.end(); i++) {
                out.put(*i);
            }
            //out << "}";
        }

        void Chars::serialize_to_cclass_context( std::ostream &out ) const {
            for( auto i=cs.begin(); i!=cs.end(); i++) {
                out.put (*i);
            }
        }

        void Chars::reset() {
            _valid = true;
            _captured = stringstream();
            state = 0;
        }

        IPattern * Chars::clone_pattern(bool withstate) const {
            Chars *copy = new Chars();
            copy->cs = cs;
            if( withstate ) {
                copy->_captured << _captured.str();
                copy->_valid = _valid;
                copy->state = state;
            }
            return copy;
        }

        bool Chars::can_transition( char c ) const {
            return state==0 && (cs.count(c) > 0);
        }

        void Chars::transition( char c ) {
            _captured.put(c);
            assert( state==0 && cs.count(c)>0);

        }

        bool Chars::accepted() const {
            return _valid && state==1;
        }

        Thing * Chars::invoke( Thing *context, string const &method, Thing *arg ) {
            (void)method; (void)arg; (void)context;
            throw runtime_error("Not implemented.");
        }

        Thing * Chars::captured_plain() {
            return new String(_captured.str());
        }

        Thing * Chars::captured_transformed() {
            return captured_plain();
        }
    }
}