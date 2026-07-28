#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>

#include "dynamicArray.h"

class Tokenizer
{
public:
    // Splits plain text into individual tokens.
    DynamicArray<std::string> tokenize(const std::string& text);

private:
    // Adds the current token to the token list if it is not empty.
    void addToken(DynamicArray<std::string>& tokens,std::string& currentToken) const;
};

#endif // TOKENIZER_H