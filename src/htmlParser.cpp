#include "htmlParser.h"

#include <cctype>

//---------------------------------------------------------
// Public Method
//---------------------------------------------------------

std::string HTMLParser::extractText(const std::string& html)
{
    // Stores the extracted visible text.
    std::string output;

    // Current position while scanning the HTML document.
    size_t i = 0;

    while (i < html.length())
    {
        //-----------------------------------------------------
        // Ignore HTML comments.
        //-----------------------------------------------------
        if (startsWithTag(html, i, "<!--"))
        {
            // Comments separate surrounding text.
            appendCharacter(output, ' ');

            i = skipComment(html, i);
            continue;
        }

        //-----------------------------------------------------
        // Ignore everything inside <script> ... </script>.
        //-----------------------------------------------------
        if (startsWithTag(html, i, "<script"))
        {
            appendCharacter(output, ' ');
            // Find the end of the opening script tag.
            size_t tagEnd = html.find('>', i);

            // Malformed HTML.
            if (tagEnd == std::string::npos)
                break;

            // Skip the complete script block.
            i = skipUntilClosingTag(html,
                                    tagEnd + 1,
                                    "</script>");

            continue;
        }

        //-----------------------------------------------------
        // Ignore everything inside <style> ... </style>.
        //-----------------------------------------------------
        if (startsWithTag(html, i, "<style"))
        {
            appendCharacter(output, ' ');
            // Find the end of the opening style tag.
            size_t tagEnd = html.find('>', i);

            // Malformed HTML.
            if (tagEnd == std::string::npos)
                break;

            // Skip the complete style block.
            i = skipUntilClosingTag(html,
                                    tagEnd + 1,
                                    "</style>");

            continue;
        }

        //-----------------------------------------------------
        // Skip all remaining HTML tags.
        //-----------------------------------------------------
        if (html[i] == '<')
        {
            size_t tagEnd = html.find('>', i);

            // Malformed HTML.
            if (tagEnd == std::string::npos)
                break;

            // Replace every tag with a single space so that
            // words from adjacent tags do not merge together.
            appendCharacter(output, ' ');

            i = tagEnd + 1;
            continue;
        }

        //-----------------------------------------------------
        // Copy visible characters.
        //-----------------------------------------------------
        appendCharacter(output, html[i]);

        i++;
    }

    //---------------------------------------------------------
    // Remove leading whitespace.
    //---------------------------------------------------------
    size_t start = 0;

    while (start < output.length() &&
           std::isspace(
               static_cast<unsigned char>(output[start])))
    {
        start++;
    }

    if (start > 0)
    {
        output.erase(0, start);
    }

    //---------------------------------------------------------
    // Remove trailing whitespace.
    //---------------------------------------------------------
    while (!output.empty() &&
           std::isspace(
               static_cast<unsigned char>(output.back())))
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