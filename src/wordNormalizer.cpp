#include "wordNormalizer.h"

#include <algorithm>
#include <cctype>

//---------------------------------------------------------
// Public Method
//---------------------------------------------------------

std::string WordNormalizer::normalize(
    const std::string& word)
{
    // Convert to lowercase.
    std::string normalized = toLowerCase(word);

    // Remove leading and trailing punctuation.
    normalized = trimPunctuation(normalized);

    // Ignore empty words.
    if (normalized.empty())
    {
        return "";
    }

    // Ignore stop words.
    if (isStopWord(normalized))
    {
        return "";
    }

    return normalized;
}

//---------------------------------------------------------
// Private Helper Methods
//---------------------------------------------------------

std::string WordNormalizer::toLowerCase(
    const std::string& word) const
{
    std::string result = word;

    for (char& ch : result)
    {
        ch = static_cast<char>(
            std::tolower(static_cast<unsigned char>(ch)));
    }

    return result;
}

std::string WordNormalizer::trimPunctuation(
    const std::string& word) const
{
    if (word.empty())
    {
        return "";
    }

    size_t start = 0;
    size_t end = word.length();

    // Remove leading punctuation.
    while (start < end &&
           std::ispunct(static_cast<unsigned char>(word[start])))
    {
        start++;
    }

    // Remove trailing punctuation.
    while (end > start &&
           std::ispunct(static_cast<unsigned char>(word[end - 1])))
    {
        end--;
    }

    return word.substr(start, end - start);
}

bool WordNormalizer::isStopWord(
    const std::string& word) const
{
    static const std::string stopWords[] =
    {
        "a",
        "an",
        "the",
        "and",
        "or",
        "but",
        "is",
        "are",
        "was",
        "were",
        "am",
        "be",
        "been",
        "being",
        "to",
        "of",
        "in",
        "on",
        "at",
        "for",
        "from",
        "by",
        "with",
        "as",
        "that",
        "this",
        "these",
        "those",
        "it",
        "its",
        "he",
        "she",
        "they",
        "them",
        "we",
        "you",
        "i"
    };

    const int count =
        sizeof(stopWords) / sizeof(stopWords[0]);

    for (int i = 0; i < count; i++)
    {
        if (word == stopWords[i])
        {
            return true;
        }
    }

    return false;
}