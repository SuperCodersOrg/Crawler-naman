#ifndef URLNORMALIZER_H
#define URLNORMALIZER_H

#include <string>

class URLNormalizer {
public:
    // Converts a raw or relative URL into a normalized absolute URL.
    // Returns an empty string if the URL is invalid.
    std::string normalize(const std::string& url,const std::string& baseUrl = "");

private:
    // Returns true if the URL starts with http:// or https://
    bool isAbsoluteURL(const std::string& url) const;

    // Resolves a relative URL using the given base URL.
    std::string resolveRelativeURL(const std::string& url,const std::string& baseUrl) const;

    // Removes ".", "..", and duplicate '/' from the path.
    std::string normalizePath(const std::string& path) const;
};

#endif