#include <gtest/gtest.h>
#include "crawler.h"

// -------------------------------
// shouldVisit()
// -------------------------------

TEST(CrawlerTest, ShouldVisitValidURL)
{
    Crawler crawler;

    EXPECT_TRUE(
        crawler.shouldVisit(
            "https://example.com",
            0,
            2
        )
    );
}

TEST(CrawlerTest, ShouldRejectEmptyURL)
{
    Crawler crawler;

    EXPECT_FALSE(
        crawler.shouldVisit(
            "",
            0,
            2
        )
    );
}

TEST(CrawlerTest, ShouldRejectDepthBeyondLimit)
{
    Crawler crawler;

    EXPECT_FALSE(
        crawler.shouldVisit(
            "https://example.com",
            5,
            2
        )
    );
}