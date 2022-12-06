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
#ifndef DESPAIR_CGI_FORM_HH
#define DESPAIR_CGI_FORM_HH

#include "tag.hh"

namespace dpcgi {

class DPCGI_DLL_API form : public tag
{
    typedef tag _SUPER;
public:
    form() noexcept; ~form() noexcept;

    inline bool has_multipart_data() const noexcept { return hasMultipartData_; }
    void multipart_data() noexcept;

    inline const string& action() const noexcept { return action_; }
    void action(const string& Action) noexcept;
    void action(string&& Action) noexcept;

private:
    static const string ATTR_ACTION_NAME_;

    string action_;
    tag submit_;
    bool hasMultipartData_;
}; // class form

} // namespace dpcgi

#endif // !DESPAIR_CGI_FORM_HH
