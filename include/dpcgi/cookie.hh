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
#ifndef DESPAIR_CGI_COOKIE_HH
#define DESPAIR_CGI_COOKIE_HH

#include "string.hh"
#include "def.h"
#include <unordered_map>

namespace dpcgi {

class DPCGI_DLL_API cookie
{
    typedef std::unordered_map<string, string> entry_table;
public:
    cookie() noexcept; ~cookie() noexcept;

    void add_entry(const string& name, const string& value) noexcept;
    bool erase(const string& name) noexcept;

    const entry_table& entries() const noexcept { return entries_; }

    inline bool empty() const noexcept { return entries_.empty(); }

private:
    entry_table entries_;
}; // class cookie

} // namespace dpcgi

#endif // !DESPAIR_CGI_COOKIE_HH
