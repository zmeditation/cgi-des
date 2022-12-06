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

#define dpcgi_attribs_push_back(wName, wValue) attribs_.push_back({ wName, wValue });


inline constexpr size_t SecondIndex = 1u;


DPCGI_NAMESPACE_BEGIN //-----------------------------------------------------------------


/*static*/ DPCGI_DLL_API tag tag::parse(const string& wStr)
{
    tag ret;

    if(wStr.at(0) != '<') {
        ret.val(wStr);
        return ret;
    } // no_else

    string tagName, tagVal;
    const auto ClosingPos = wStr.rfind("</");
    const auto FirstClosingAngularBracket = wStr.find('>');

    if(ClosingPos != string::npos) {
        tagName = wStr.substr(ClosingPos + 2u);
        tagName.pop_back();
        ret.name(std::move(tagName));
    } else {
        tagName = wStr.substr(SecondIndex, tagName.length() - 2u);
        
        ret.name(std::move(tagName));
        ret.self_closed(true);
    } // endif

    const string TagProps = wStr.substr(1, FirstClosingAngularBracket);
    std::istringstream iss(TagProps);
    string tmp;
    iss >> tmp;
    while(iss >> tmp)
    {
        std::pair<string, string> pair = split_config_str(tmp);
        //const auto EqPos = tmp.find('=');
        //const string name = tmp.substr(0u, EqPos);
        //string value = tmp.substr(EqPos + 2u);
        
        //$ last attribute may end with >, so remove it (and the closing quote too).
        if(pair.second.back() != '>') pair.second.resize(pair.second.length() - 1u);
        else pair.second.resize(pair.second.length() - 2u);
        
        ret.add_attrib(std::move(pair.first), std::move(pair.second));
    }
    // endwhile

    tagVal = wStr.substr(
        FirstClosingAngularBracket + 1u, ClosingPos - FirstClosingAngularBracket - 1u
    );
    ret.val(std::move(tagVal));

    return ret;
}


DPCGI_DLL_API tag::tag() noexcept : selfClosed_(false), hasEol_(true) {}


DPCGI_DLL_API tag::tag(const string& wName) : 
    name_(wName), selfClosed_(false), hasEol_(true)
{}


/*virtual*/ DPCGI_DLL_API tag::~tag() noexcept {}


DPCGI_DLL_API void tag::add_attrib(const string& wName, const string& wValue) noexcept
{
    dpcgi_attribs_push_back(wName, wValue);
}


DPCGI_DLL_API void tag::add_attrib(string&& wName, string&& wValue) noexcept
{
    dpcgi_attribs_push_back(wName, wValue);
}


DPCGI_DLL_API string tag::end() const noexcept
{
    if(selfClosed_ || name_.empty()) return "";
    return "</" + name_ + '>';
}


DPCGI_DLL_API string tag::str() const noexcept
{
    std::ostringstream oss;

    oss << '<' << name_;

    for(const auto& attrib : attribs_) {
        oss << ' ' << attrib.name << "=\"" << attrib.value << "\"";
    } // endfor
    
    if(selfClosed_) {
        oss << " />";
        if(this->hasEol_) oss << '\n';
    } else {
        oss << '>';
        for(const auto& child : children_) oss << '\n' << child->str();
        oss << val_ << this->end();
        if(this->hasEol_) oss << '\n';
    } // endif

    return oss.str();
}


DPCGI_DLL_API tag::attrib_ptr tag::find_attrib(const string& name) noexcept
{
    return std::find_if(attribs_.begin(), attribs_.end(), [&](const attribute& lAttrib){
        return (name == lAttrib.name);
    });
}


DPCGI_DLL_API std::ostream& operator<<(std::ostream& wStream, const tag& wTag)
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
