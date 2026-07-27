#include <gtest/gtest.h>
#include <string>

#include "fetcher.h"

// ------------------------------------------------
// Valid URL
// ------------------------------------------------

TEST(FetcherTest, FetchValidPage)
{
    Fetcher fetcher;

    std::string html =
        fetcher.fetch("https://example.com");

    EXPECT_FALSE(html.empty());
}

// ------------------------------------------------
// Invalid domain
// ------------------------------------------------

TEST(FetcherTest, InvalidDomain)
{
    Fetcher fetcher;

    EXPECT_EQ(
        fetcher.fetch("https://this-domain-should-not-exist-123456789.com"),
        ""
    );
}

// ------------------------------------------------
// Invalid URL format
// ------------------------------------------------

TEST(FetcherTest, InvalidURL)
{
    Fetcher fetcher;

    EXPECT_EQ(
        fetcher.fetch("not_a_url"),
        ""
    );
}

// ------------------------------------------------
// Empty URL
// ------------------------------------------------

TEST(FetcherTest, EmptyURL)
{
    Fetcher fetcher;

    EXPECT_EQ(
        fetcher.fetch(""),
        ""
    );
}

// ------------------------------------------------
// 404 Page
// ------------------------------------------------

TEST(FetcherTest, NotFoundPage)
{
    Fetcher fetcher;

    EXPECT_EQ(
        fetcher.fetch("https://example.com/thispagedoesnotexist"),
        ""
    );
}

// ------------------------------------------------
// Redirect
// ------------------------------------------------

TEST(FetcherTest, FollowRedirect)
{
    Fetcher fetcher;

    std::string html =
        fetcher.fetch("http://example.com");

    EXPECT_FALSE(html.empty());
}

// ------------------------------------------------
// HTTPS
// ------------------------------------------------

TEST(FetcherTest, HTTPSPage)
{
    Fetcher fetcher;

    EXPECT_FALSE(
        fetcher.fetch("https://www.example.com").empty()
    );
}

// ------------------------------------------------
// HTML contains expected content
// ------------------------------------------------

TEST(FetcherTest, ContainsHTML)
{
    Fetcher fetcher;

    std::string html =
        fetcher.fetch("https://example.com");

    EXPECT_NE(
        html.find("<html"),
        std::string::npos
    );
}

// ------------------------------------------------
// Multiple fetches
// ------------------------------------------------

TEST(FetcherTest, MultipleRequests)
{
    Fetcher fetcher;

    EXPECT_FALSE(fetcher.fetch("https://example.com").empty());
    EXPECT_FALSE(fetcher.fetch("https://www.iana.org").empty());
}

// ------------------------------------------------
// Consecutive calls
// ------------------------------------------------

TEST(FetcherTest, ConsecutiveFetches)
{
    Fetcher fetcher;

    std::string first =
        fetcher.fetch("https://example.com");

    std::string second =
        fetcher.fetch("https://example.com");

    EXPECT_FALSE(first.empty());
    EXPECT_FALSE(second.empty());
}