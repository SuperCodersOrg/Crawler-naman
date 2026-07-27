#include <gtest/gtest.h>
#include "urlNormalizer.h"

class URLNormalizerTest : public ::testing::Test {
protected:
    URLNormalizer normalizer;
};

// ----------------------
// Absolute URLs
// ----------------------

TEST_F(URLNormalizerTest, AbsoluteURL)
{
    EXPECT_EQ(
        normalizer.normalize("https://example.com"),
        "https://example.com/"
    );
}

TEST_F(URLNormalizerTest, LowercaseSchemeAndHost)
{
    EXPECT_EQ(
        normalizer.normalize("HTTP://EXAMPLE.COM"),
        "http://example.com/"
    );
}

// ----------------------
// Relative URLs
// ----------------------

TEST_F(URLNormalizerTest, RelativeURL)
{
    EXPECT_EQ(
        normalizer.normalize(
            "about.html",
            "https://example.com/docs/index.html"
        ),
        "https://example.com/docs/about.html"
    );
}

TEST_F(URLNormalizerTest, RootRelativeURL)
{
    EXPECT_EQ(
        normalizer.normalize(
            "/images/logo.png",
            "https://example.com/docs/index.html"
        ),
        "https://example.com/images/logo.png"
    );
}

// ----------------------
// Query URLs
// ----------------------

TEST_F(URLNormalizerTest, QueryOnlyURL)
{
    EXPECT_EQ(
        normalizer.normalize(
            "?id=10",
            "https://example.com/page.html"
        ),
        "https://example.com/page.html?id=10"
    );
}

// ----------------------
// Protocol-relative URLs
// ----------------------

TEST_F(URLNormalizerTest, ProtocolRelativeURL)
{
    EXPECT_EQ(
        normalizer.normalize(
            "//cdn.example.com/lib.js",
            "https://example.com"
        ),
        "https://cdn.example.com/lib.js"
    );
}

// ----------------------
// Dot segments
// ----------------------

TEST_F(URLNormalizerTest, RemoveCurrentDirectory)
{
    EXPECT_EQ(
        normalizer.normalize(
            "https://example.com/a/./b"
        ),
        "https://example.com/a/b"
    );
}

TEST_F(URLNormalizerTest, RemoveParentDirectory)
{
    EXPECT_EQ(
        normalizer.normalize(
            "https://example.com/a/b/../c"
        ),
        "https://example.com/a/c"
    );
}

TEST_F(URLNormalizerTest, MultipleParentDirectories)
{
    EXPECT_EQ(
        normalizer.normalize(
            "https://example.com/a/b/c/../../d"
        ),
        "https://example.com/a/d"
    );
}

// ----------------------
// Duplicate slashes
// ----------------------

TEST_F(URLNormalizerTest, DuplicateSlashes)
{
    EXPECT_EQ(
        normalizer.normalize(
            "https://example.com////a////b///"
        ),
        "https://example.com/a/b/"
    );
}

// ----------------------
// Fragment removal
// ----------------------

TEST_F(URLNormalizerTest, RemoveFragment)
{
    EXPECT_EQ(
        normalizer.normalize(
            "https://example.com/page#section"
        ),
        "https://example.com/page"
    );
}

TEST_F(URLNormalizerTest, IgnoreFragmentOnlyLink)
{
    EXPECT_EQ(
        normalizer.normalize(
            "#section",
            "https://example.com"
        ),
        ""
    );
}

// ----------------------
// Unsupported protocols
// ----------------------

TEST_F(URLNormalizerTest, IgnoreJavascript)
{
    EXPECT_EQ(
        normalizer.normalize("javascript:alert(1)"),
        ""
    );
}

TEST_F(URLNormalizerTest, IgnoreMailto)
{
    EXPECT_EQ(
        normalizer.normalize("mailto:test@example.com"),
        ""
    );
}

TEST_F(URLNormalizerTest, IgnoreTelephone)
{
    EXPECT_EQ(
        normalizer.normalize("tel:+911234567890"),
        ""
    );
}

// ----------------------
// Empty input
// ----------------------

TEST_F(URLNormalizerTest, EmptyURL)
{
    EXPECT_EQ(
        normalizer.normalize(""),
        ""
    );
}

TEST_F(URLNormalizerTest, RelativeWithoutBaseURL)
{
    EXPECT_EQ(
        normalizer.normalize(
            "about.html",
            ""
        ),
        ""
    );
}

// ----------------------
// Path normalization
// ----------------------

TEST_F(URLNormalizerTest, PreserveTrailingSlash)
{
    EXPECT_EQ(
        normalizer.normalize(
            "https://example.com/a/b/"
        ),
        "https://example.com/a/b/"
    );
}

TEST_F(URLNormalizerTest, NormalizeComplexPath)
{
    EXPECT_EQ(
        normalizer.normalize(
            "https://example.com//a///./b/../c/"
        ),
        "https://example.com/a/c/"
    );
}