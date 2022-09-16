#ifndef DESPAIR_CGI_TAG_HH
#define DESPAIR_CGI_TAG_HH

#include <ostream>
#include <string>
#include <vector>


namespace dpcgi {


class tag
{
public:
    static tag parse(const std::string& wStr);

    tag();
    tag(const std::string& wName);
    virtual ~tag();

    void add_attrib(const std::string& wName, const std::string& wValue);
    std::string end();

    friend std::ostream& operator<<(std::ostream&, const tag&);

protected:
    std::string name_;
    struct attribute { std::string name, value; };
    std::vector<attribute> attribs_;
    std::string value;
    bool selfClosed_;
};


std::ostream& operator<<(std::ostream& wStream, const dpcgi::tag& wTag);


}; // namespace dpcgi


// std::ostream& operator<<(std::ostream& wStream, const dpcgi::tag& wTag);


#endif // !DESPAIR_CGI_TAG_HH
