#include <gtest/gtest.h>

#include "tokenizer.h"

class TokenizerTest : public ::testing::Test
{
protected:
    Tokenizer tokenizer;
};

TEST_F(TokenizerTest, EmptyString)
{
    DynamicArray<std::string> tokens = tokenizer.tokenize("");

    EXPECT_EQ(tokens.getSize(), 0);
}

TEST_F(TokenizerTest, SingleWord)
{
    DynamicArray<std::string> tokens =
        tokenizer.tokenize("Hello");

    ASSERT_EQ(tokens.getSize(), 1);
    EXPECT_EQ(tokens[0], "Hello");
}

TEST_F(TokenizerTest, MultipleWords)
{
    DynamicArray<std::string> tokens =
        tokenizer.tokenize("Hello World");

    ASSERT_EQ(tokens.getSize(), 2);

    EXPECT_EQ(tokens[0], "Hello");
    EXPECT_EQ(tokens[1], "World");
}

TEST_F(TokenizerTest, MultipleSpaces)
{
    DynamicArray<std::string> tokens =
        tokenizer.tokenize("Hello    World");

    ASSERT_EQ(tokens.getSize(), 2);

    EXPECT_EQ(tokens[0], "Hello");
    EXPECT_EQ(tokens[1], "World");
}

TEST_F(TokenizerTest, LeadingSpaces)
{
    DynamicArray<std::string> tokens =
        tokenizer.tokenize("     Hello World");

    ASSERT_EQ(tokens.getSize(), 2);

    EXPECT_EQ(tokens[0], "Hello");
    EXPECT_EQ(tokens[1], "World");
}

TEST_F(TokenizerTest, TrailingSpaces)
{
    DynamicArray<std::string> tokens =
        tokenizer.tokenize("Hello World     ");

    ASSERT_EQ(tokens.getSize(), 2);

    EXPECT_EQ(tokens[0], "Hello");
    EXPECT_EQ(tokens[1], "World");
}

TEST_F(TokenizerTest, TabsAndNewlines)
{
    DynamicArray<std::string> tokens =
        tokenizer.tokenize("Hello\tWorld\nTokenizer");

    ASSERT_EQ(tokens.getSize(), 3);

    EXPECT_EQ(tokens[0], "Hello");
    EXPECT_EQ(tokens[1], "World");
    EXPECT_EQ(tokens[2], "Tokenizer");
}

TEST_F(TokenizerTest, OnlyWhitespace)
{
    DynamicArray<std::string> tokens =
        tokenizer.tokenize("   \t\n   ");

    EXPECT_EQ(tokens.getSize(), 0);
}

TEST_F(TokenizerTest, PreservesPunctuation)
{
    DynamicArray<std::string> tokens =
        tokenizer.tokenize("Hello, World!");

    ASSERT_EQ(tokens.getSize(), 2);

    EXPECT_EQ(tokens[0], "Hello,");
    EXPECT_EQ(tokens[1], "World!");
}

TEST_F(TokenizerTest, PreservesNumbers)
{
    DynamicArray<std::string> tokens =
        tokenizer.tokenize("123 456 789");

    ASSERT_EQ(tokens.getSize(), 3);

    EXPECT_EQ(tokens[0], "123");
    EXPECT_EQ(tokens[1], "456");
    EXPECT_EQ(tokens[2], "789");
}

TEST_F(TokenizerTest, MixedWordsAndNumbers)
{
    DynamicArray<std::string> tokens =
        tokenizer.tokenize("Apple 123 Banana 456");

    ASSERT_EQ(tokens.getSize(), 4);

    EXPECT_EQ(tokens[0], "Apple");
    EXPECT_EQ(tokens[1], "123");
    EXPECT_EQ(tokens[2], "Banana");
    EXPECT_EQ(tokens[3], "456");
}

TEST_F(TokenizerTest, SingleCharacterTokens)
{
    DynamicArray<std::string> tokens =
        tokenizer.tokenize("A B C");

    ASSERT_EQ(tokens.getSize(), 3);

    EXPECT_EQ(tokens[0], "A");
    EXPECT_EQ(tokens[1], "B");
    EXPECT_EQ(tokens[2], "C");
}