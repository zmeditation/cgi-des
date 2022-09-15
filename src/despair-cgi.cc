#include "tag.hh"
#include <iostream>


int main()
{
    dpcgi::tag tag("dummy_tag");
    tag.add_attrib("first_attrib", "no value");
    std::cout << tag << tag.end();
    return 0;
}
