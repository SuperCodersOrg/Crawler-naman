#include <gtest/gtest.h>

#include "wordNormalizer.h"

class WordNormalizerTest : public ::testing::Test
{
protected:
    WordNormalizer normalizer;
};

TEST_F(WordNormalizerTest, EmptyString)
{
    EXPECT_EQ(normalizer.normalize(""), "");
}

TEST_F(WordNormalizerTest, LowercaseConversion)
{
    EXPECT_EQ(normalizer.normalize("HELLO"), "hello");
}

TEST_F(WordNormalizerTest, MixedCaseConversion)
{
    EXPECT_EQ(normalizer.normalize("HeLLo"), "hello");
}

TEST_F(WordNormalizerTest, TrimLeadingPunctuation)
{
    EXPECT_EQ(normalizer.normalize("...hello"), "hello");
}

TEST_F(WordNormalizerTest, TrimTrailingPunctuation)
{
    EXPECT_EQ(normalizer.normalize("hello!!!"), "hello");
}

TEST_F(WordNormalizerTest, TrimBothSidesPunctuation)
{
    EXPECT_EQ(normalizer.normalize("\"hello,\""), "hello");
}

TEST_F(WordNormalizerTest, PreserveInternalPunctuation)
{
    EXPECT_EQ(normalizer.normalize("can't"), "can't");
}

TEST_F(WordNormalizerTest, IgnoreOnlyPunctuation)
{
    EXPECT_EQ(normalizer.normalize("!!!"), "");
}

TEST_F(WordNormalizerTest, IgnoreSingleStopWord)
{
    EXPECT_EQ(normalizer.normalize("the"), "");
}

TEST_F(WordNormalizerTest, IgnoreStopWordAfterLowercase)
{
    EXPECT_EQ(normalizer.normalize("THE"), "");
}

TEST_F(WordNormalizerTest, IgnoreStopWordWithPunctuation)
{
    EXPECT_EQ(normalizer.normalize("the,"), "");
}

TEST_F(WordNormalizerTest, NonStopWordRemains)
{
    EXPECT_EQ(normalizer.normalize("computer"), "computer");
}

TEST_F(WordNormalizerTest, NumberRemainsUnchanged)
{
    EXPECT_EQ(normalizer.normalize("12345"), "12345");
}

TEST_F(WordNormalizerTest, AlphaNumericWord)
{
    EXPECT_EQ(normalizer.normalize("CS101"), "cs101");
}

TEST_F(WordNormalizerTest, SingleCharacterNonStopWord)
{
    EXPECT_EQ(normalizer.normalize("X"), "x");
}

TEST_F(WordNormalizerTest, SingleCharacterStopWord)
{
    EXPECT_EQ(normalizer.normalize("I"), "");
}

TEST_F(WordNormalizerTest, WhitespaceNotModified)
{
    EXPECT_EQ(normalizer.normalize(" hello "), " hello ");
}

TEST_F(WordNormalizerTest, ComplexWord)
{
    EXPECT_EQ(normalizer.normalize("(Computer!)"), "computer");
}