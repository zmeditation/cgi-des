#include "tag.hh"


namespace dpcgi {


/*static*/ tag tag::parse(const std::string& wStr)
{
    return tag();
}


tag::tag() : selfClosed_(false) {}


tag::tag(const std::string& wName) : name_(wName), selfClosed_(false)
{}


tag::~tag() {}


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


} // namespace dpcgi


//std::ostream& operator<<(std::ostream& wStream, const dpcgi::tag& wTag)
//{
//    std::cout << "Out!\n";
//    return wStream << wTag;
//}

