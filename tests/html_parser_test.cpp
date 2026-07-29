#include <gtest/gtest.h>

#include "htmlParser.h"

TEST(HTMLParserTest, EmptyHTML)
{
    HTMLParser parser;

    EXPECT_EQ(parser.extractText(""), "");
}

TEST(HTMLParserTest, PlainText)
{
    HTMLParser parser;

    EXPECT_EQ(parser.extractText("Hello World"),
              "Hello World");
}

TEST(HTMLParserTest, RemovesHTMLTags)
{
    HTMLParser parser;

    std::string html =
        "<html><body>Hello World</body></html>";

    EXPECT_EQ(parser.extractText(html),
              "Hello World");
}

TEST(HTMLParserTest, HandlesNestedTags)
{
    HTMLParser parser;

    std::string html =
        "<div><p>Hello <b>World</b></p></div>";

    EXPECT_EQ(parser.extractText(html),
              "Hello World");
}

TEST(HTMLParserTest, IgnoresScriptContent)
{
    HTMLParser parser;

    std::string html =
        "<body>"
        "Hello "
        "<script>"
        "alert('Hello');"
        "</script>"
        "World"
        "</body>";

    EXPECT_EQ(parser.extractText(html),
              "Hello World");
}

TEST(HTMLParserTest, IgnoresStyleContent)
{
    HTMLParser parser;

    std::string html =
        "<body>"
        "Hello "
        "<style>"
        "body { color:red; }"
        "</style>"
        "World"
        "</body>";

    EXPECT_EQ(parser.extractText(html),
              "Hello World");
}

TEST(HTMLParserTest, IgnoresComments)
{
    HTMLParser parser;

    std::string html =
        "Hello<!-- This is a comment -->World";

    EXPECT_EQ(parser.extractText(html),
              "Hello World");
}

TEST(HTMLParserTest, CollapsesWhitespace)
{
    HTMLParser parser;

    std::string html =
        "<p>Hello</p>\n\n\t<p>World</p>";

    EXPECT_EQ(parser.extractText(html),
              "Hello World");
}

TEST(HTMLParserTest, TrimsLeadingAndTrailingWhitespace)
{
    HTMLParser parser;

    std::string html =
        "     <p>Hello World</p>      ";

    EXPECT_EQ(parser.extractText(html),
              "Hello World");
}

TEST(HTMLParserTest, HandlesEmptyHTMLTags)
{
    HTMLParser parser;

    std::string html =
        "<html><body></body></html>";

    EXPECT_EQ(parser.extractText(html),
              "");
}

TEST(HTMLParserTest, HandlesMalformedHTML)
{
    HTMLParser parser;

    std::string html =
        "<html><body>Hello World";

    EXPECT_EQ(parser.extractText(html),
              "Hello World");
}

TEST(HTMLParserTest, HandlesMultipleScriptBlocks)
{
    HTMLParser parser;

    std::string html =
        "<script>abc()</script>"
        "Hello "
        "<script>xyz()</script>"
        "World";

    EXPECT_EQ(parser.extractText(html),
              "Hello World");
}

TEST(HTMLParserTest, HandlesMultipleStyleBlocks)
{
    HTMLParser parser;

    std::string html =
        "<style>a</style>"
        "Hello "
        "<style>b</style>"
        "World";

    EXPECT_EQ(parser.extractText(html),
              "Hello World");
}

TEST(HTMLParserTest, SupportsCaseInsensitiveTags)
{
    HTMLParser parser;

    std::string html =
        "<BODY>"
        "Hello"
        "<SCRIPT>"
        "abc();"
        "</SCRIPT>"
        "World"
        "</BODY>";

    EXPECT_EQ(parser.extractText(html),
              "Hello World");
}

TEST(HTMLParserTest, PreservesVisiblePunctuation)
{
    HTMLParser parser;

    std::string html =
        "<p>Hello, World!</p>";

    EXPECT_EQ(parser.extractText(html),
              "Hello, World!");
}