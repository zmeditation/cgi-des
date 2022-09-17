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
#include "tag.hh"


DPCGI_NAMESPACE_BEGIN //-----------------------------------------------------------------


/*static*/ tag tag::parse(const std::string& wStr)
{
    return tag();
}


tag::tag() noexcept : selfClosed_(false) {}


tag::tag(const std::string& wName) : name_(wName), selfClosed_(false)
{}


/*virtual*/ tag::~tag() noexcept {}


void tag::add_attrib(const std::string& wName, const std::string& wValue)
{
    attribs_.push_back({ wName, wValue });
}


std::string tag::end()
{
    if(selfClosed_) return "";
    return "</" + name_ + '>';
}


std::ostream& operator<<(std::ostream& wStream, const tag& wTag)
{
    wStream << '<' << wTag.name_;
    for(auto& attrib : wTag.attribs_) {
        wStream << ' ' << attrib.name << "=\"" << attrib.value << "\"";
    }
    if(wTag.selfClosed_) wStream << " />";
    else wStream << '>';
    return wStream;
}


DPCGI_NAMESPACE_END //-------------------------------------------------------------------


// std::ostream& operator<<(std::ostream& wStream, const dpcgi::tag& wTag)
// {
//    std::cout << "Out!\n";
//    return dpcgi::operator<<(wStream, wTag);
// }
