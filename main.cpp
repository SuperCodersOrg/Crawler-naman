#include <iostream>
#include <string>

#include "wordNormalizer.h"

void printResult(WordNormalizer& normalizer,
                 const std::string& input)
{
    std::string output = normalizer.normalize(input);

    std::cout << "Input : \"" << input << "\"\n";
    std::cout << "Output: \"" << output << "\"\n";
    std::cout << "----------------------------------------\n";
}

int main()
{
    WordNormalizer normalizer;

    std::cout << "=========================================\n";
    std::cout << "Test 1 - Lowercase Conversion\n\n";
    printResult(normalizer, "HELLO");

    std::cout << "=========================================\n";
    std::cout << "Test 2 - Mixed Case\n\n";
    printResult(normalizer, "HeLLo");

    std::cout << "=========================================\n";
    std::cout << "Test 3 - Trailing Punctuation\n\n";
    printResult(normalizer, "hello,");

    std::cout << "=========================================\n";
    std::cout << "Test 4 - Leading Punctuation\n\n";
    printResult(normalizer, "(world");

    std::cout << "=========================================\n";
    std::cout << "Test 5 - Both Sides Punctuation\n\n";
    printResult(normalizer, "\"search!\"");

    std::cout << "=========================================\n";
    std::cout << "Test 6 - Stop Word (the)\n\n";
    printResult(normalizer, "the");

    std::cout << "=========================================\n";
    std::cout << "Test 7 - Stop Word (THE)\n\n";
    printResult(normalizer, "THE");

    std::cout << "=========================================\n";
    std::cout << "Test 8 - Stop Word (An)\n\n";
    printResult(normalizer, "An");

    std::cout << "=========================================\n";
    std::cout << "Test 9 - Normal Word\n\n";
    printResult(normalizer, "Computer");

    std::cout << "=========================================\n";
    std::cout << "Test 10 - Empty String\n\n";
    printResult(normalizer, "");

    std::cout << "=========================================\n";
    std::cout << "Test 11 - Only Punctuation\n\n";
    printResult(normalizer, "!!!");

    std::cout << "=========================================\n";
    std::cout << "Test 12 - Number\n\n";
    printResult(normalizer, "2026");

    std::cout << "=========================================\n";
    std::cout << "Test 13 - Alphanumeric\n\n";
    printResult(normalizer, "Version2");

    std::cout << "=========================================\n";
    std::cout << "Test 14 - C++\n\n";
    printResult(normalizer, "C++");

    std::cout << "=========================================\n";
    std::cout << "Test 15 - Node.js\n\n";
    printResult(normalizer, "Node.js");

    std::cout << "=========================================\n";
    std::cout << "Test 16 - Multiple Punctuation\n\n";
    printResult(normalizer, "...Hello!!!");

    return 0;
}