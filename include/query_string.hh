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
#ifndef DESPAIR_CGI_QUERY_STRING_HH
#define DESPAIR_CGI_QUERY_STRING_HH
#include "string.hh"
#include <unordered_map>

namespace dpcgi {

class query_string
{
public:
    typedef std::unordered_map<string, string> string_table;

    query_string() noexcept;
    ~query_string() noexcept;

    inline const string_table& queries() const noexcept { return queries_; }
    inline const char* raw() const noexcept { return raw_; }
    inline size_t size() const noexcept { return queries_.size(); }
    inline bool empty() const noexcept { return queries_.empty(); }

private:
    string_table queries_;
    const char* raw_;
}; // class query_string

} // namespace dpcgi

#endif // !DESPAIR_CGI_QUERY_STRING_HH
