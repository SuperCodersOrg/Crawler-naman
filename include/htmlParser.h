#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include <string>

class HTMLParser
{
public:
    HTMLParser() = default;

    // Extracts visible text from an HTML document.
    std::string extractText(const std::string& html);

private:
    // Returns true if the current position starts with the given tag.
    bool startsWithTag(const std::string& html,size_t pos,const std::string& tag) const;

    // Skips characters until the specified closing tag is found.
    size_t skipUntilClosingTag(const std::string& html, size_t pos,const std::string& closingTag) const;

    // Skips an HTML comment.
    size_t skipComment(const std::string& html,size_t pos) const;

    // Collapses consecutive whitespace characters into a single space.
    void appendCharacter(std::string& output, char ch) const;
};

#endif 