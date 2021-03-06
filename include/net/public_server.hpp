#ifndef RHIZOME_NET_PUBLIC_SERVER
#define RHIZOME_NET_PUBLIC_SERVER

#include <cwctype>
#include <string>
#include <codecvt>
#include <locale>

using std::wstring;
using std::string;

#include "sdt/article.hpp"
#include "types/uuid.hpp"
#include "types/dir.hpp"
#include "alphabet.hpp"

using rhizome::sdt::Article;
using rhizome::types::UUID;
using rhizome::types::Dir;
using rhizome::alphabet::Classifier;

namespace rhizome {
    namespace net {
        /// This encodes slashes as well, so use with caution.
        string url_encode_utf8( wstring const &docname );
        string url_encode_windows1252( wstring const &docname );

        /// Let's assume you have an apache 2 install somewhere.
        /// This class is for reading its configuration to see if
        /// we have write-permission somewhere so we can publish
        /// dynamically generated documents using a regular-old server.
        class PublicServer {
            wstring root_dir;
            UUID intance_id;
            Classifier classifier;
        public:
            /// Where is your web directory? (or a subdirectory that this process has access to)
            /// Using PublicServer to push out static pages will put them in a temporary
            /// folder. These folders are (er., will be) swept as necessary.
            PublicServer(string root_dir);

            void write_document( wstring filename, Article *article );
        };

        /* To consider: is there an application of this framework that does not
           use the in-built client-server architecture? Of course! Most applications
           won't need a standalone server. The whole point of this class is to enable
           publishing /consciously and intentionally/ to a public-facing web-server.
           For example, 'professional' blogging, research notes, etc. */
        
        /* To consider further: if your thoughts are not private, where is the
           sanctum in which the sub-conscious, the creative part of our being
           can flourish? Must it disguise itself with a name in a world of egos?
           Am I subject or object when I set out to know myself? */

        /* My personal feelings on the subject are evident here. Creativity is by no
           means decent, and only a cruel and sadistic government criminalizes the 
           domain of thought. A reasonable compromise is found in clearly stated 
           community standards and transparent, even-handed enforcement of the same.
           Clearly minors are subject to the whims and biases of their parents until 
           the age of majority. Perhaps appropriate content controls could be based 
           on age, as it is with movie tickets.

           Appropriate content controls should be built into the media itself. A mere
           designation of 'adult' and 'not adult' content encoded into a pages meta-
           data should allow 'parental' browsers to exclude adult content. Failure to
           adhere to this content labelling scheme could be curbed by the levying of
           fines. This would lead (I think) content creators to err on the side of 
           caution. In general, I would prefer my ideas be considered by adults. I
           would adhere to any /transparent/ content-labelling scheme that my government 
           would recommend. As it stands, there is no 'top shelf' that cannot be
           reached by young, tech savvy post-millenials. Instead, current schemes
           undoubtedly rely on farmed content-flagging labor. Really, these schemes
           create hidden blacklists. Any scholar of US history can tell you why these
           lists are bad. */
    }
}

#endif