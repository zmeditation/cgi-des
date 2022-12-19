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

TEST(cookie, empty_cookie) {
    dpcgi::cookie cookie;
    EXPECT_TRUE(cookie.empty());
}

TEST(cookie, dummy) {
    dpcgi::cookie dummyCookie;
    dummyCookie.add_entry("username", "kql2");
    const auto FirstEntry = dummyCookie.entries().begin();
    EXPECT_EQ(FirstEntry->first, "username");
    EXPECT_EQ(FirstEntry->second, "kql2");
}

TEST(cookie, intentionally_fail) {
    EXPECT_TRUE(false);
}