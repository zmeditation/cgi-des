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
#include <query_string.hh>
#include <iostream>
#include <sstream>

int main()
{
    dpcgi::query_string qs;
    std::ostringstream oss;
    if(!qs.empty()) oss << qs.queries().begin()->first << " = " << qs.queries().begin()->second;
    else oss.str("[empty]");

    std::cout << "Content-type:text/html\r\n\r\n";

    std::cout << "<html>\n";
    std::cout << "<head>\n";
    std::cout << "<title>Query String Example</title>\n";
    std::cout << "</head>\n";
    std::cout << "<body>\n";
    std::cout << "<h1>Query Entries</h1>\n";
    for(const auto& query : qs.queries()) {
        std::cout << "<h2>k=" << query.first << " v=" << query.second << "</h2>\n";
    } // endfor
    std::cout << "</body>\n";
    std::cout << "</html>\n";
    
    return 0;
}
