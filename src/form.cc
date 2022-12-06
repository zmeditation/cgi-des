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
#include "form.hh"


DPCGI_NAMESPACE_BEGIN


DPCGI_DLL_API form::form() noexcept : _SUPER("form"), submit_("input"), hasMultipartData_(false)
{
    submit_.add_attrib("type", "submit");
    this->_SUPER::add_child(submit_);
}


DPCGI_DLL_API form::~form () noexcept {}


DPCGI_DLL_API void form::multipart_data() noexcept
{
    if(hasMultipartData_) return;
    this->_SUPER::add_attrib("enctype", "multipart/form-data");
    hasMultipartData_ = true;
}


DPCGI_DLL_API void form::action(const string& Action) noexcept
{
    dpcgi_tag_set_string(action_, ATTR_ACTION_NAME_, Action);
}


DPCGI_DLL_API  void form::action(string&& Action) noexcept
{
    dpcgi_tag_set_string(action_, ATTR_ACTION_NAME_, Action);
}


/* static */ DPCGI_DLL_API const string form::ATTR_ACTION_NAME_ = "action";


DPCGI_NAMESPACE_END
