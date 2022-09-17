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
#ifndef DESPAIR_CGI_TAG_HH
#define DESPAIR_CGI_TAG_HH

#include <ostream>
#include <string>
#include <vector>


namespace dpcgi {

enum class result : uint32_t {
    success = 0, err_op_denied    
};

class tag
{
public:
    static tag parse(const std::string& wStr);

    tag() noexcept;
    tag(const std::string& wName);
    virtual ~tag() noexcept;

    void add_attrib(const std::string& wName, const std::string& wValue = "");
    std::string end();

    inline const std::string& name() const noexcept { return name_; }
    inline void name(const std::string& wName) noexcept { name_ = wName; }
    
    inline bool self_closed() const noexcept { return selfClosed_; }
    inline bool self_closed(bool wYesNo) noexcept { selfClosed_ = wYesNo; }
    
    inline bool empty() const noexcept { return name_.empty(); }

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
