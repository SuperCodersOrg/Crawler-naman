#include <gtest/gtest.h>
#include <cstdio>

#include "pageStore.h"

class PageStorageTest : public ::testing::Test
{
protected:
    const std::string file = "../storage/test_pages.txt";

    void SetUp() override
    {
        std::remove(file.c_str());
    }

    void TearDown() override
    {
        std::remove(file.c_str());
    }
};

// ------------------------------------------------
// Empty storage
// ------------------------------------------------

TEST_F(PageStorageTest, InitiallyEmpty)
{
    PageStorage storage(file);

    EXPECT_EQ(storage.pageCount(), 0);
    EXPECT_FALSE(storage.hasPage("https://example.com"));
}

// ------------------------------------------------
// Store one page
// ------------------------------------------------

TEST_F(PageStorageTest, StoreSinglePage)
{
    PageStorage storage(file);

    storage.storePage(
        "https://example.com",
        "<html>Hello</html>",
        0
    );

    EXPECT_EQ(storage.pageCount(), 1);
    EXPECT_TRUE(storage.hasPage("https://example.com"));
}

// ------------------------------------------------
// Retrieve stored page
// ------------------------------------------------

TEST_F(PageStorageTest, GetStoredPage)
{
    PageStorage storage(file);

    storage.storePage(
        "https://example.com",
        "<html>Hello</html>",
        0
    );

    EXPECT_EQ(
        storage.getPage("https://example.com"),
        "<html>Hello</html>\n"
    );
}

// ------------------------------------------------
// Unknown page
// ------------------------------------------------

TEST_F(PageStorageTest, GetUnknownPage)
{
    PageStorage storage(file);

    EXPECT_EQ(
        storage.getPage("https://unknown.com"),
        ""
    );
}

// ------------------------------------------------
// Multiple pages
// ------------------------------------------------

TEST_F(PageStorageTest, StoreMultiplePages)
{
    PageStorage storage(file);

    storage.storePage("https://a.com", "A", 0);
    storage.storePage("https://b.com", "B", 1);
    storage.storePage("https://c.com", "C", 2);

    EXPECT_EQ(storage.pageCount(), 3);

    EXPECT_TRUE(storage.hasPage("https://a.com"));
    EXPECT_TRUE(storage.hasPage("https://b.com"));
    EXPECT_TRUE(storage.hasPage("https://c.com"));
}

// ------------------------------------------------
// URL lookup by ID
// ------------------------------------------------

TEST_F(PageStorageTest, GetURLByID)
{
    PageStorage storage(file);

    storage.storePage("https://google.com", "A", 0);
    storage.storePage("https://github.com", "B", 1);

    EXPECT_EQ(
        storage.getURLByID(1),
        "https://google.com"
    );

    EXPECT_EQ(
        storage.getURLByID(2),
        "https://github.com"
    );
}

// ------------------------------------------------
// Invalid IDs
// ------------------------------------------------

TEST_F(PageStorageTest, InvalidID)
{
    PageStorage storage(file);

    storage.storePage("https://google.com", "A", 0);

    EXPECT_EQ(storage.getURLByID(0), "");
    EXPECT_EQ(storage.getURLByID(-1), "");
    EXPECT_EQ(storage.getURLByID(5), "");
}

// ------------------------------------------------
// Duplicate page update
// ------------------------------------------------

TEST_F(PageStorageTest, UpdateExistingPage)
{
    PageStorage storage(file);

    storage.storePage(
        "https://example.com",
        "Old",
        0
    );

    storage.storePage(
        "https://example.com",
        "New",
        1
    );

    EXPECT_EQ(storage.pageCount(), 1);

    EXPECT_EQ(
        storage.getPage("https://example.com"),
        "New\n"
    );
}

// ------------------------------------------------
// Persistence
// ------------------------------------------------

TEST_F(PageStorageTest, ReloadStorage)
{
    {
        PageStorage storage(file);

        storage.storePage(
            "https://google.com",
            "Google",
            0
        );

        storage.storePage(
            "https://github.com",
            "GitHub",
            1
        );
    }

    PageStorage storage(file);

    EXPECT_EQ(storage.pageCount(), 2);

    EXPECT_TRUE(storage.hasPage("https://google.com"));
    EXPECT_TRUE(storage.hasPage("https://github.com"));

    EXPECT_EQ(
        storage.getPage("https://google.com"),
        "Google\n"
    );

    EXPECT_EQ(
        storage.getPage("https://github.com"),
        "GitHub\n"
    );
}

// ------------------------------------------------
// Empty URL
// ------------------------------------------------

TEST_F(PageStorageTest, IgnoreEmptyURL)
{
    PageStorage storage(file);

    storage.storePage(
        "",
        "HTML",
        0
    );

    EXPECT_EQ(storage.pageCount(), 0);
}

// ------------------------------------------------
// Empty HTML
// ------------------------------------------------

TEST_F(PageStorageTest, EmptyHTML)
{
    PageStorage storage(file);

    storage.storePage(
        "https://example.com",
        "",
        0
    );

    EXPECT_EQ(
        storage.getPage("https://example.com"),
        ""
    );
}

// ------------------------------------------------
// Many pages
// ------------------------------------------------

TEST_F(PageStorageTest, ManyPages)
{
    PageStorage storage(file);

    for(int i = 0; i < 100; i++)
    {
        storage.storePage(
            "https://site" + std::to_string(i) + ".com",
            "HTML",
            i
        );
    }

    EXPECT_EQ(storage.pageCount(), 100);

    EXPECT_TRUE(storage.hasPage("https://site0.com"));
    EXPECT_TRUE(storage.hasPage("https://site50.com"));
    EXPECT_TRUE(storage.hasPage("https://site99.com"));
}