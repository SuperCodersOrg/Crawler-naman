#include <iostream>
#include <string>

#include "tokenizer.h"

void printTokens(const DynamicArray<std::string>& tokens)
{
    std::cout << "Number of Tokens: " << tokens.getSize() << "\n";

    for (int i = 0; i < tokens.getSize(); i++)
    {
        std::cout << "[" << i << "] "
                  << "\"" << tokens[i] << "\"\n";
    }
}

int main()
{
    Tokenizer tokenizer;

    std::string tests[] =
    {
        "Hello World",

        "   Hello     World   ",

        "This is a tokenizer test.",

        "C++ is awesome!",

        "",

        "OneWord",

        "Line1\nLine2\nLine3",

        "Word1\tWord2\t\tWord3",

        "Hello, World! This is GPT.",

        "   Multiple   spaces\tand\nnewlines   together   "
    };

    int numberOfTests = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < numberOfTests; i++)
    {
        std::cout << "=========================================\n";
        std::cout << "Test " << i + 1 << "\n\n";

        std::cout << "Input:\n";
        std::cout << "\"" << tests[i] << "\"\n\n";

        DynamicArray<std::string> tokens =
            tokenizer.tokenize(tests[i]);

        std::cout << "Output:\n";
        printTokens(tokens);

        std::cout << "\n";
    }

    return 0;
}