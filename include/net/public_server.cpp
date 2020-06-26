#include "public_server.hpp"

#include <fstream>
#include <iostream>
#include <codecvt>
#include <locale>
#include <cwchar>

namespace rhizome {
    namespace net {
        string url_encode_utf8( wstring const &docname ) {
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            
        }

        string url_encode_windows1252( wstring const &docname ) {
            
        }

        PublicServer::PublicServer( string root_dir ) {
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            this->root_dir = converter.from_bytes(root_dir);
            
        }

        void
        PublicServer::write_document( wstring filename, Article *article ) {
            
        }
    }
}