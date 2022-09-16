#include "dpcgi_pch.hh"
#include "html_document.hh"

constexpr const char* const EMPTY =
R"(<html>
    <head>
        <title>untitled</title>
    </head>
    <body>
        <h2>Hello, jackass!</h2>
    </body>
</html>)";

DPCGI_NAMESPACE_BEGIN


html_document::html_document() noexcept {}
html_document::~html_document() noexcept {}

std::string html_document::str() const noexcept { return EMPTY; }

DPCGI_NAMESPACE_END
