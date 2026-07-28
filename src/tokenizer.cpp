#include "tokenizer.h"

#include <cctype>

//---------------------------------------------------------
// Public Method
//---------------------------------------------------------

DynamicArray<std::string> Tokenizer::tokenize(
    const std::string& text)
{
    // Stores all extracted tokens.
    DynamicArray<std::string> tokens;

    // Stores the token currently being built.
    std::string currentToken;

    for (char ch : text)
    {
        // Whitespace marks the end of a token.
        if (std::isspace(static_cast<unsigned char>(ch)))
        {
            addToken(tokens, currentToken);
        }
        else
        {
            currentToken.push_back(ch);
        }
    }

    // Add the final token if one exists.
    addToken(tokens, currentToken);

    return tokens;
}

//---------------------------------------------------------
// Private Helper Method
//---------------------------------------------------------

void Tokenizer::addToken(
    DynamicArray<std::string>& tokens,
    std::string& currentToken) const
{
    // Ignore empty tokens produced by multiple spaces.
    if (!currentToken.empty())
    {
        tokens.append(currentToken);
        currentToken.clear();
    }
}