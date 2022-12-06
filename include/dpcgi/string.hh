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
#ifndef DESPAIR_CGI_STRING_HH
#define DESPAIR_CGI_STRING_HH
#include <string>

namespace dpcgi {

typedef std::string                 string;
typedef std::pair<string, string>   string_pair;

inline string trim_str(const string& str) {
    return str.substr(1u, str.length() - 1u);
}

//$ Split a string with format key=value.
inline string_pair split_config_str(const string& str)
{
    auto EqPos = str.find('=');
    if(EqPos != string::npos) return {
        str.substr(0, EqPos),
        str.substr(EqPos + 2u)
    };
    return {};
}

} // namespace dpgci

#endif // !DESPAIR_CGI_STRING_HH
