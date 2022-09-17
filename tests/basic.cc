#include <html_document.hh>
#include <tag.hh>
#include <gtest/gtest.h>

TEST(dpcgi, tag) {
    dpcgi::tag myTag;
    EXPECT_TRUE(myTag.name().empty());
    myTag = dpcgi::tag("html");
    EXPECT_FALSE(myTag.name().empty());
}


TEST(dpcgi, html_document) {
    dpcgi::html_document doc;
    auto tag_Html = dpcgi::tag("html");
    auto tag_Head = dpcgi::tag("head");
    auto tag_Body = dpcgi::tag("body");

    EXPECT_EQ(doc.add_tag(tag_Html), dpcgi::result::err_op_denied);
    EXPECT_EQ(doc.add_tag(tag_Head), dpcgi::result::err_op_denied);
    EXPECT_EQ(doc.add_tag(tag_Body), dpcgi::result::err_op_denied);
}
