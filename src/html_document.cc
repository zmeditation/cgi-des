/****************************************************************************************
MIT License

Copyright (c) 2022 流陳光

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
****************************************************************************************/
#include "dpcgi_pch.hh"
#include "html_document.hh"

#define DPCGI_html_document_add_tag(wTag) \
    if(_THIS::tagIsForbidden(wTag)) return result::err_op_denied;\
    tags_.push_back(wTag);\
    return result::success;


DPCGI_NAMESPACE_BEGIN


DPCGI_DLL_API html_document::html_document() noexcept : title_("dpcgi_untitled") {}
DPCGI_DLL_API html_document::~html_document() noexcept {}

DPCGI_DLL_API result html_document::add_tag(const tag& wTag) noexcept
{
    if(_THIS::tagIsForbidden(wTag)) return result::err_op_denied;
    tags_.push_back(wTag);
    return result::success;
}


DPCGI_DLL_API result html_document::add_tag(tag&& wTag) noexcept
{
    DPCGI_html_document_add_tag(wTag);
}


DPCGI_DLL_API string html_document::str() const noexcept
{
    std::ostringstream oss;
    oss << 
        _THIS::CONTENT_TYPE_STR_ <<
        "<html>\n" <<
        "<head>\n "
        ;
    if(charSet_.length()) {
        oss << " <meta charset=\"" << charSet_ << "\" />\n";
    } // no_else
    oss << "<title>" << title_ << "</title>" << "</head>\n" <<
        "<body>\n"
        ;
    
    for(const auto& tag : tags_) {
        oss << tag.str();
    } // endfor

    oss << "</body></html>\n";

    return oss.str();
}


/*static*/ DPCGI_DLL_API const string html_document::CONTENT_TYPE_STR_ 
    = "Content-type:text/html\r\n\r\n";


/*static*/ DPCGI_DLL_API bool html_document::tagIsForbidden(const tag& wTag)
{
    return ( forbiddenTags_.find(wTag.name()) != forbiddenTags_.end() );
}


/*static*/ DPCGI_DLL_API const std::set<string> html_document::forbiddenTags_ = {
    "body", "head", "html"
};


DPCGI_NAMESPACE_END
