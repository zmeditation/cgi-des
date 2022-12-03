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

#define TAG_NAME_IMG_BEG "img"
#define TAG_NAME_IMG_END "</img>"

TEST(tag, parse) {
    dpcgi::tag myTag = dpcgi::tag::parse("gibberish");
    EXPECT_EQ(myTag.name(), "a");
}


TEST(tag, html_empty) {
    dpcgi::tag myTag;
    EXPECT_TRUE(myTag.eol());
    EXPECT_TRUE(myTag.name().empty());
    
    myTag = dpcgi::tag("html");
    EXPECT_FALSE(myTag.name().empty());
    EXPECT_EQ(myTag.name(), "html");
    EXPECT_EQ(myTag.end(), "</html>");
    EXPECT_EQ(myTag.str(), "<html> </html>\n");
    
    myTag.is_child(false);
    EXPECT_EQ(myTag.str(), "<html></html>\n");

    myTag.eol(false);
    EXPECT_FALSE(myTag.eol());
    EXPECT_EQ(myTag.str(), "<html></html>");
}


TEST(tag, img) {
    dpcgi::tag imgTag(TAG_NAME_IMG_BEG);
    imgTag.add_attrib("src", "http://img.co/star.png");

    EXPECT_EQ(imgTag.name(), TAG_NAME_IMG_BEG);
    EXPECT_EQ(imgTag.end(), TAG_NAME_IMG_END);
    EXPECT_TRUE(imgTag.eol());
    EXPECT_TRUE(imgTag.is_child());
}


TEST(dpcgi, tag_form) {
    dpcgi::form emptyForm;
    EXPECT_EQ(emptyForm.name(), "form");
    EXPECT_EQ(emptyForm.end(), "</form>");
    EXPECT_TRUE(emptyForm.is_child());

    emptyForm.multipart_data();
    const auto MultipartAttrib = emptyForm.find_attrib("enctype");
    EXPECT_EQ(MultipartAttrib->value, "multipart/form-data");
}
