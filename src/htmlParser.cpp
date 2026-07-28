#include "htmlParser.h"

#include <cctype>

//---------------------------------------------------------
// Public Method
//---------------------------------------------------------

std::string HTMLParser::extractText(const std::string& html)
{
    std::string output;

    size_t i = 0;

    while (i < html.length())
    {
        // Skip HTML comments
        if (startsWithTag(html, i, "<!--"))
        {
            i = skipComment(html, i);
            continue;
        }

        // Skip <script>...</script>
        if (startsWithTag(html, i, "<script"))
        {
            size_t tagEnd = html.find('>', i);

            if (tagEnd == std::string::npos)
                break;

            i = skipUntilClosingTag(html, tagEnd + 1, "</script>");
            continue;
        }

        // Skip <style>...</style>
        if (startsWithTag(html, i, "<style"))
        {
            size_t tagEnd = html.find('>', i);

            if (tagEnd == std::string::npos)
                break;

            i = skipUntilClosingTag(html, tagEnd + 1, "</style>");
            continue;
        }

        // Skip normal HTML tags
        if (html[i] == '<')
        {
            size_t tagEnd = html.find('>', i);

            if (tagEnd == std::string::npos)
                break;

            appendCharacter(output, ' ');
            i = tagEnd + 1;
            continue;
        }

        appendCharacter(output, html[i]);
        i++;
    }

    // Remove trailing whitespace
    while (!output.empty() &&
           std::isspace(static_cast<unsigned char>(output.back())))
    {
        output.pop_back();
    }

    return output;
}

//---------------------------------------------------------
// Private Helper Methods
//---------------------------------------------------------

bool HTMLParser::startsWithTag(const std::string& html,
                               size_t pos,
                               const std::string& tag) const
{
    if (pos + tag.length() > html.length())
        return false;

    for (size_t i = 0; i < tag.length(); i++)
    {
        char a = std::tolower(
            static_cast<unsigned char>(html[pos + i]));

        char b = std::tolower(
            static_cast<unsigned char>(tag[i]));

        if (a != b)
            return false;
    }

    return true;
}

size_t HTMLParser::skipUntilClosingTag(
    const std::string& html,
    size_t pos,
    const std::string& closingTag) const
{
    while (pos < html.length())
    {
        if (startsWithTag(html, pos, closingTag))
        {
            size_t end = html.find('>', pos);

            if (end == std::string::npos)
                return html.length();

            return end + 1;
        }

        pos++;
    }

    return html.length();
}

size_t HTMLParser::skipComment(
    const std::string& html,
    size_t pos) const
{
    size_t end = html.find("-->", pos);

    if (end == std::string::npos)
        return html.length();

    return end + 3;
}

void HTMLParser::appendCharacter(
    std::string& output,
    char ch) const
{
    if (std::isspace(static_cast<unsigned char>(ch)))
    {
        if (output.empty())
            return;

        if (output.back() == ' ')
            return;

        output.push_back(' ');
    }
    else
    {
        output.push_back(ch);
    }
}