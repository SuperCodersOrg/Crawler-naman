#include <iostream>
#include <vector>

#include "htmlParser.h"

int main()
{
    HTMLParser parser;

    std::vector<std::string> tests =
    {
        "<div>Hello <b>World</b></div>",

        "",

        "<script>alert('Hello');</script>",

        "Hello<!-- Ignore Me -->World",

        "<a href=\"https://google.com\">Google</a>",

        "<div>Hello",

        "<style>body{color:red;}</style>Hello",

        "<h1>Title</h1><p>This is a paragraph.</p>",

        "<div><span><b>Nested</b></span> Tags</div>"
    };

    for (size_t i = 0; i < tests.size(); i++)
    {
        std::cout << "Test " << i + 1 << '\n';
        std::cout << "Input:\n";
        std::cout << tests[i] << "\n\n";

        std::cout << "Output:\n";
        std::cout << parser.extractText(tests[i]) << "\n";

        std::cout << "----------------------------------------\n";
    }

    return 0;
}