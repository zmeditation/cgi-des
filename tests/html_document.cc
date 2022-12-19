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
#include "tests_pch.hh"

constexpr const char* EMPTY_HTML_DOCUMENT_AS_STR = 
    "Content-type:text/html\r\n\r\n"
    "<html>\n"
    "<head>\n"
    " <title>dpcgi_untitled</title></head>\n"
    "<body>\n"
    "</body></html>\n"
    ;

TEST(html_document, empty) {
    dpcgi::html_document doc;
    EXPECT_EQ(doc.str(), EMPTY_HTML_DOCUMENT_AS_STR);
}


TEST(html_document, add_tag) {
    dpcgi::html_document doc;
    const auto tag_Html = dpcgi::tag("html");
    const auto tag_Head = dpcgi::tag("head");
    const auto tag_Body = dpcgi::tag("body");
    const auto tag_Foo = dpcgi::tag("foo");
    const auto tag_Clgt = dpcgi::tag("clgt");

    EXPECT_EQ(doc.add_tag(tag_Html), dpcgi::result::err_op_denied);
    EXPECT_EQ(doc.add_tag(tag_Head), dpcgi::result::err_op_denied);
    EXPECT_EQ(doc.add_tag(tag_Body), dpcgi::result::err_op_denied);
    EXPECT_EQ(doc.add_tag(tag_Foo), dpcgi::result::success);
    EXPECT_EQ(doc.add_tag(tag_Clgt), dpcgi::result::success);
}


TEST(html_document, charset) {
    dpcgi::html_document doc;
    doc.char_set("UTF-8");
    EXPECT_EQ(doc.char_set(), "UTF-8");
}
