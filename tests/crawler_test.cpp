#include <gtest/gtest.h>
#include "crawler.h"

// --------------------------------------------
// Invalid seed URL
// --------------------------------------------

TEST(CrawlerTest, EmptySeedURL)
{
    Crawler crawler;

    EXPECT_NO_THROW(
        crawler.crawl("", 2, 10)
    );
}

// --------------------------------------------
// Invalid URL format
// --------------------------------------------

TEST(CrawlerTest, InvalidSeedURL)
{
    Crawler crawler;

    EXPECT_NO_THROW(
        crawler.crawl("not_a_url", 2, 10)
    );
}

// --------------------------------------------
// Zero max pages
// --------------------------------------------

TEST(CrawlerTest, ZeroMaxPages)
{
    Crawler crawler;

    EXPECT_NO_THROW(
        crawler.crawl("https://example.com", 2, 0)
    );
}

// --------------------------------------------
// Zero max depth
// --------------------------------------------

TEST(CrawlerTest, ZeroMaxDepth)
{
    Crawler crawler;

    EXPECT_NO_THROW(
        crawler.crawl("https://example.com", 0, 1)
    );
}

// --------------------------------------------
// Valid crawl
// --------------------------------------------

TEST(CrawlerTest, ValidCrawl)
{
    Crawler crawler;

    EXPECT_NO_THROW(
        crawler.crawl("https://example.com", 1, 1)
    );
}