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

#include "def.h"
#include "string.hh"
#include <ostream>
#include <vector>


namespace dpcgi {

enum class result : uint32_t {
    success = 0, err_op_denied    
};

class DPCGI_DLL_API tag
{
    struct attribute { string name, value; };
    typedef std::vector<attribute> attrib_table;
    typedef std::vector<attribute>::iterator attrib_ptr;
public:
    static tag parse(const string& wStr);

    tag() noexcept;
    tag(const string& wName);
    virtual ~tag() noexcept;

    void add_attrib(const string& name, const string& nalue = "");
    void add_child(const tag& child) noexcept { children_.push_back(&child); }
    string end() const noexcept;

    string str() const noexcept;

    inline const string& name() const noexcept { return name_; }
    inline void name(const string& name) noexcept { name_ = name; }

    inline const string& val() const noexcept { return val_; }
    inline void val(const string& wVal) noexcept { val_ = wVal; }
    
    inline bool self_closed() const noexcept { return selfClosed_; }
    inline void self_closed(bool wYesNo) noexcept { selfClosed_ = wYesNo; }

    attrib_ptr find_attrib(const string& name) noexcept;

    //$ EOL: if set, an EOL will be inserted to the end of ::str() result.
    inline bool eol() const noexcept { return hasEol_; }
    inline void eol(bool YesNo) noexcept { hasEol_ = YesNo; }

    inline bool is_child() const noexcept { return isChild_; }
    inline void is_child(bool YesNo) noexcept { isChild_ = YesNo; }
    
    inline bool empty() const noexcept { return name_.empty(); }
    inline bool unnamed() const noexcept { return name_.empty(); }
    inline bool null_attrib(const attrib_ptr& attrib) const noexcept {
        return attrib == attribs_.end();
    }

    friend std::ostream& operator<<(std::ostream&, const tag&);

protected:
    string name_;
    std::vector<attribute> attribs_;
    string val_;
    std::vector<const tag*> children_;
    bool selfClosed_;
    bool hasEol_;
    bool isChild_;
};

std::ostream& operator<<(std::ostream& wStream, const dpcgi::tag& wTag);

} // namespace dpcgi

// std::ostream& operator<<(std::ostream& wStream, const dpcgi::tag& wTag);


#endif // !DESPAIR_CGI_TAG_HH
