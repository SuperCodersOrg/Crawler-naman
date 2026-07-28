#ifndef WORDNORMALIZER_H
#define WORDNORMALIZER_H

#include <string>

class WordNormalizer
{
public:
    // Normalizes a single token.
    // Returns an empty string if the token should be ignored.
    std::string normalize(const std::string& word);

private:
    // Converts all alphabetic characters to lowercase.
    std::string toLowerCase(const std::string& word) const;

    // Removes punctuation from the beginning and end of a word.
    std::string trimPunctuation(const std::string& word) const;

    // Checks whether a word is a stop word.
    bool isStopWord(const std::string& word) const;
};

#endif