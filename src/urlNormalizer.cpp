#include "urlNormalizer.h"

#include <algorithm>
#include <cctype>
#include <string>

bool URLNormalizer::isAbsoluteURL(const std::string& url) const {
    std::string temp = url;

    std::transform(temp.begin(),
                   temp.end(),
                   temp.begin(),
                   [](unsigned char c)
                   {
                       return std::tolower(c);
                   });
    return (temp.length() >= 7 && temp.compare(0, 7, "http://") == 0) || (temp.length() >= 8 && temp.compare(0, 8, "https://") == 0);
}

std::string URLNormalizer::resolveRelativeURL(const std::string& url,const std::string& baseUrl) const {
    if (url.empty())
        return "";
    
    // Query-only URL
    if (url[0] == '?')
    {
        std::size_t fragmentPos = baseUrl.find('#');

        if (fragmentPos != std::string::npos)
            return baseUrl.substr(0, fragmentPos) + url;

        return baseUrl + url;
    }

    // Root-relative URL
    if (url[0] == '/') {
        std::size_t schemePos = baseUrl.find("://");
        if (schemePos == std::string::npos)
            return "";
        std::size_t hostEnd = baseUrl.find('/', schemePos + 3);

        if (hostEnd == std::string::npos)
            return baseUrl + url;

        return baseUrl.substr(0, hostEnd) + url;
    }

    // Relative URL
    std::size_t lastSlash = baseUrl.find_last_of('/');

    if (lastSlash == std::string::npos)
        return "";

    return baseUrl.substr(0, lastSlash + 1) + url;
}

std::string URLNormalizer::normalizePath(const std::string& path) const
{
    if (path.empty())
        return "/";

    bool hadTrailingSlash =
        (path.length() > 1 && path.back() == '/');

    std::string result;
    size_t i = 0;

    while (i < path.length())
    {
        // Skip duplicate '/'
        while (i < path.length() && path[i] == '/')
            i++;

        std::string token;

        while (i < path.length() && path[i] != '/')
        {
            token += path[i];
            i++;
        }

        // Ignore "."
        if (token.empty() || token == ".")
            continue;

        // Handle ".."
        if (token == "..")
        {
            if (!result.empty())
            {
                // Remove last directory
                size_t lastSlash = result.find_last_of('/');

                if (lastSlash == std::string::npos)
                {
                    result.clear();
                }
                else
                {
                    result.erase(lastSlash);
                }
            }

            continue;
        }

        result += "/";
        result += token;
    }

    if (result.empty())
        result = "/";

    // Preserve trailing '/'
    if (hadTrailingSlash &&
        result.back() != '/')
    {
        result += '/';
    }

    return result;
}

std::string URLNormalizer::normalize(const std::string& url,
                                     const std::string& baseUrl) {

    if (url.empty())
        return "";

    // Ignore fragment-only links
    if (url[0] == '#')
        return "";

    // Ignore JavaScript links
    if (url.rfind("javascript:", 0) == 0)
        return "";

    // Ignore mail links
    if (url.rfind("mailto:", 0) == 0)
        return "";

    // Ignore telephone links
    if (url.rfind("tel:", 0) == 0)
        return "";


    std::string absoluteURL = url;

    // Handle protocol-relative URL
    if (url.rfind("//", 0) == 0)
    {
        std::size_t schemePos = baseUrl.find("://");

        if (schemePos == std::string::npos)
            return "";

        std::string scheme = baseUrl.substr(0, schemePos);

        absoluteURL = scheme + ":" + url;
    }

    // Resolve relative URL
    else if (!isAbsoluteURL(url)) {

        if (baseUrl.empty())
            return "";

        absoluteURL = resolveRelativeURL(url, baseUrl);
    }

    // Remove fragment
    std::size_t fragmentPos = absoluteURL.find('#');
    if (fragmentPos != std::string::npos)
        absoluteURL.erase(fragmentPos);

    // Find scheme
    std::size_t schemePos = absoluteURL.find("://");

    if (schemePos == std::string::npos)
        return "";

    std::string scheme = absoluteURL.substr(0, schemePos);

    std::transform(scheme.begin(),
                   scheme.end(),
                   scheme.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    // Find host
    std::size_t hostStart = schemePos + 3;
    std::size_t pathStart = absoluteURL.find('/', hostStart);

    std::string host;
    std::string path = "/";

    if (pathStart == std::string::npos) {

        host = absoluteURL.substr(hostStart);

    } else {

        host = absoluteURL.substr(hostStart,pathStart - hostStart);
        path = absoluteURL.substr(pathStart);
    }

    // Convert host to lowercase
    std::transform(host.begin(),host.end(),host.begin(),[](unsigned char c){ return std::tolower(c); });

    // Remove duplicate '/'
    std::string cleanedPath;

    for (char ch : path) {

        if (ch == '/' &&
            !cleanedPath.empty() &&
            cleanedPath.back() == '/')
            continue;

        cleanedPath += ch;
    }

    path = normalizePath(cleanedPath);

    return scheme + "://" + host + path;
}
