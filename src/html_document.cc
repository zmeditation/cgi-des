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

constexpr const char* const EMPTY =
R"(<html>
    <head>
        <title>untitled</title>
    </head>
    <body>
        <h2>Hello, jackass!</h2>
    </body>
</html>)";

DPCGI_NAMESPACE_BEGIN


html_document::html_document() noexcept {}
html_document::~html_document() noexcept {}

result html_document::add_tag(const tag& wTag) noexcept
{
    if(_THIS::tagIsForbidden(wTag)) return result::err_op_denied;
    tags_.push_back(wTag);
    return result::success;
}


result html_document::add_tag(tag&& wTag) noexcept{}


string html_document::str() const noexcept { return EMPTY; }


/*static*/ bool html_document::tagIsForbidden(const tag& wTag)
{
    return ( forbiddenTags_.find(wTag.name()) != forbiddenTags_.end() );
}


/*static*/ const std::set<string> html_document::forbiddenTags_ = {
    "body", "head", "html"
};


DPCGI_NAMESPACE_END
