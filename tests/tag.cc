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


#define TAG_GIBBERISH_NAME_BEG "gibberish"
#define TAG_GIBBERISH_NAME_END  "</" TAG_GIBBERISH_NAME_BEG ">"
#define TAG_GIBBERISH_VALUE     "TagValue"
TEST(tag, parse) {
    dpcgi::tag myTag = dpcgi::tag::parse(
        "<" TAG_GIBBERISH_NAME_BEG " att1=\"val1\">TagValue" TAG_GIBBERISH_NAME_END
    );
    EXPECT_EQ(myTag.name(), TAG_GIBBERISH_NAME_BEG);
    EXPECT_EQ(myTag.end(), TAG_GIBBERISH_NAME_END);
    EXPECT_EQ(myTag.val(), "TagValue");
    EXPECT_FALSE(myTag.self_closed());

    const auto attr1 = myTag.find_attrib("attr1");
    EXPECT_TRUE(myTag.null_attrib(attr1));

    const auto attr2 = myTag.find_attrib("att1");
    EXPECT_EQ(attr2->name, "att1");
    EXPECT_EQ(attr2->value, "val1");
}


TEST(tag, html_empty) {
    dpcgi::tag myTag;
    EXPECT_TRUE(myTag.eol());
    EXPECT_TRUE(myTag.name().empty());
    
    myTag = dpcgi::tag("html");
    EXPECT_FALSE(myTag.name().empty());
    EXPECT_EQ(myTag.name(), "html");
    EXPECT_EQ(myTag.end(), "</html>");
    EXPECT_EQ(myTag.str(), "<html></html>\n");

    myTag.eol(false);
    EXPECT_FALSE(myTag.eol());
    EXPECT_EQ(myTag.str(), "<html></html>");
}


#define TEST_TAG_ID_RVALUE "rvalue_fancy_id"
TEST(tag, id) {
    const struct {
        dpcgi::string name = "span";
        dpcgi::string end = "</" + name + ">";
        dpcgi::string emptyStr = "";
        dpcgi::string lValueStr = "lvalue_str";
    } should_be;
    dpcgi::tag myTag(should_be.name);
    EXPECT_EQ(myTag.name(), should_be.name);
    EXPECT_EQ(myTag.end(), should_be.end);
    EXPECT_EQ(myTag.id(), should_be.emptyStr);
    EXPECT_TRUE(myTag.has_no_id());

    myTag.id(TEST_TAG_ID_RVALUE);
    EXPECT_EQ(myTag.id(), TEST_TAG_ID_RVALUE);

    myTag.id(should_be.lValueStr);
    EXPECT_EQ(myTag.id(), should_be.lValueStr);
}


#define TAG_IMG_NAME_BEG        "img"
#define TAG_IMG_NAME_END        ("</" TAG_IMG_NAME_BEG ">")
#define TAG_IMG_ATTR_SRC_NAME   "src"
#define TAG_IMG_ATTR_SRC_VAL    "http://img.co/star.png"
TEST(tag, name_is_img) {
    const dpcgi::string AttrSrcName = TAG_IMG_ATTR_SRC_NAME;
    const struct {
        dpcgi::string imgTagName = TAG_IMG_NAME_BEG;
        dpcgi::string imgTagEnd = TAG_IMG_NAME_END;
        dpcgi::string attribSrcName = TAG_IMG_ATTR_SRC_NAME;
        dpcgi::string attribSrcVal = TAG_IMG_ATTR_SRC_VAL;
    } should_be;

    dpcgi::tag imgTag(TAG_IMG_NAME_BEG);
    imgTag.add_attrib(TAG_IMG_ATTR_SRC_NAME, TAG_IMG_ATTR_SRC_VAL);

    EXPECT_EQ(imgTag.name(), should_be.imgTagName);
    EXPECT_EQ(imgTag.end(), should_be.imgTagEnd);
    EXPECT_EQ(imgTag.find_attrib(AttrSrcName)->name, should_be.attribSrcName);
    EXPECT_EQ(imgTag.find_attrib(AttrSrcName)->value, should_be.attribSrcVal);
    EXPECT_TRUE(imgTag.eol());
}


TEST(tag, name_is_form) {
    dpcgi::form emptyForm;
    EXPECT_EQ(emptyForm.name(), "form");
    EXPECT_EQ(emptyForm.end(), "</form>");
    EXPECT_FALSE(emptyForm.has_multipart_data());

    emptyForm.multipart_data();
    const auto MultipartAttrib = emptyForm.find_attrib("enctype");
    EXPECT_EQ(MultipartAttrib->value, "multipart/form-data");
    EXPECT_TRUE(emptyForm.has_multipart_data());
}


#define TAG_PARSE_UNNAMED_VALUE "tag with no angular brackets"
TEST(tag, parse_unnamed) {
    dpcgi::tag unnamed = dpcgi::tag::parse(TAG_PARSE_UNNAMED_VALUE);
    EXPECT_TRUE(unnamed.name().empty());
    EXPECT_EQ(unnamed.val(), TAG_PARSE_UNNAMED_VALUE);
}


TEST(tag, val) {
    dpcgi::tag htmlTag("html");
    dpcgi::tag headTag("head");
    dpcgi::tag bodyTag("body");
    htmlTag.val(
        headTag.str() + '\n' + bodyTag.str()
    );
    const dpcgi::string HtmlTagVal = 
        "<head></head>\n\n"
        "<body></body>\n"
        ;
    EXPECT_EQ(htmlTag.val(), HtmlTagVal);
}


TEST(tag, tag_img) {
    dpcgi::tag_img imgTag;
    EXPECT_EQ(imgTag.name(), TAG_IMG_NAME_BEG);
    EXPECT_EQ(imgTag.end(), TAG_IMG_NAME_END);
    EXPECT_TRUE(imgTag.val().empty());
}
