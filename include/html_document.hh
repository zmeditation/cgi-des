#ifndef DPCGI_HTML_DOCUMENT_HH
#define DPCGI_HTML_DOCUMENT_HH

#include <string>

namespace dpcgi {

class html_document
{
public:
    html_document() noexcept; ~html_document() noexcept;

    std::string str() const noexcept;
    
    inline const std::string& title() const noexcept { return title_; }
    inline void title(const std::string& wTitle) noexcept { title_ = wTitle; }

private:
    std::string title_;
};

}

#endif // !DPCGI_HTML_DOCUMENT_HH
