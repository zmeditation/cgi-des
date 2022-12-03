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
#include "query_string.hh"

//#ifdef DPCGI_DEBUG
#include <iostream>
//#endif


DPCGI_NAMESPACE_BEGIN


DPCGI_DLL_API query_string::query_string() noexcept : raw_(getenv("QUERY_STRING"))
{
    if(raw_ == nullptr) return;
    std::istringstream iss(raw_);
    string query;
    while(std::getline(iss, query, '&'))
    {
        const size_t EqPos = query.find('=');
        if(EqPos == string::npos) continue;
        const std::pair<string, string> pair{
            query.substr(0, EqPos), query.substr(EqPos+1)
        };
        queries_.insert(std::move(pair));
    }
    // endwhile
}


DPCGI_DLL_API query_string::~query_string() noexcept {}


DPCGI_NAMESPACE_END
