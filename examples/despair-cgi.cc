#include "html_document.hh"
#include "tag.hh"
#include <iostream>


int main()
{
    std::cout << "Content-type:text/html\r\n\r\n";

    dpcgi::html_document doc;
    std::cout << doc.str() << '\n';

    dpcgi::tag tag("dummy_tag");
    tag.add_attrib("first_attrib", "no value");
    std::cout << tag << tag.end();
    return 0;
}
