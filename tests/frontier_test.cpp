#include <gtest/gtest.h>
#include <cstdio>

#include "frontier.h"

class FrontierTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        std::remove("../storage/frontier.txt");
    }

    void TearDown() override
    {
        std::remove("../storage/frontier.txt");
    }
};

// ------------------------------------------------
// Empty frontier
// ------------------------------------------------

TEST_F(FrontierTest, InitiallyEmpty)
{
    Frontier frontier;

    EXPECT_TRUE(frontier.empty());
    EXPECT_EQ(frontier.size(), 0);
}

// ------------------------------------------------
// Push one element
// ------------------------------------------------

TEST_F(FrontierTest, PushOneElement)
{
    Frontier frontier;

    frontier.push({"https://example.com", 0});

    EXPECT_FALSE(frontier.empty());
    EXPECT_EQ(frontier.size(), 1);

    EXPECT_EQ(frontier.front().url, "https://example.com");
    EXPECT_EQ(frontier.front().depth, 0);
}

// ------------------------------------------------
// FIFO order
// ------------------------------------------------

TEST_F(FrontierTest, FIFOOrder)
{
    Frontier frontier;

    frontier.push({"A", 0});
    frontier.push({"B", 1});
    frontier.push({"C", 2});

    EXPECT_EQ(frontier.pop().url, "A");
    EXPECT_EQ(frontier.pop().url, "B");
    EXPECT_EQ(frontier.pop().url, "C");

    EXPECT_TRUE(frontier.empty());
}

// ------------------------------------------------
// Front does not remove element
// ------------------------------------------------

TEST_F(FrontierTest, FrontDoesNotRemove)
{
    Frontier frontier;

    frontier.push({"Google", 1});

    EXPECT_EQ(frontier.front().url, "Google");
    EXPECT_EQ(frontier.size(), 1);
}

// ------------------------------------------------
// Multiple pushes
// ------------------------------------------------

TEST_F(FrontierTest, MultiplePushes)
{
    Frontier frontier;

    for (int i = 0; i < 10; i++)
    {
        frontier.push(
            {
                "URL" + std::to_string(i),
                i
            });
    }

    EXPECT_EQ(frontier.size(), 10);
}

// ------------------------------------------------
// Push and pop
// ------------------------------------------------

TEST_F(FrontierTest, PushPop)
{
    Frontier frontier;

    frontier.push({"A", 0});
    frontier.push({"B", 1});

    frontier.pop();

    EXPECT_EQ(frontier.front().url, "B");
    EXPECT_EQ(frontier.size(), 1);
}

// ------------------------------------------------
// Copy constructor
// ------------------------------------------------

TEST_F(FrontierTest, CopyConstructor)
{
    Frontier frontier;

    frontier.push({"Google", 0});
    frontier.push({"GitHub", 1});

    Frontier copy(frontier);

    EXPECT_EQ(copy.size(), 2);

    EXPECT_EQ(copy.pop().url, "Google");
    EXPECT_EQ(copy.pop().url, "GitHub");
}

// ------------------------------------------------
// Assignment operator
// ------------------------------------------------

TEST_F(FrontierTest, AssignmentOperator)
{
    Frontier frontier;

    frontier.push({"A", 0});
    frontier.push({"B", 1});

    Frontier other;

    other = frontier;

    EXPECT_EQ(other.size(), 2);

    EXPECT_EQ(other.pop().url, "A");
    EXPECT_EQ(other.pop().url, "B");
}

// ------------------------------------------------
// Persistence
// ------------------------------------------------

TEST_F(FrontierTest, CheckpointPersistence)
{
    {
        Frontier frontier;

        frontier.push({"https://google.com", 0});
        frontier.push({"https://github.com", 1});

        frontier.checkpoint();
    }

    Frontier recovered;

    EXPECT_EQ(recovered.size(), 2);

    EXPECT_EQ(recovered.pop().url, "https://google.com");
    EXPECT_EQ(recovered.pop().url, "https://github.com");
}

// ------------------------------------------------
// Clear persistence
// ------------------------------------------------

TEST_F(FrontierTest, ClearDisk)
{
    {
        Frontier frontier;

        frontier.push({"https://google.com", 0});
        frontier.checkpoint();
        frontier.clearDisk();
    }

    Frontier recovered;

    EXPECT_TRUE(recovered.empty());
}

// ------------------------------------------------
// Large queue
// ------------------------------------------------

TEST_F(FrontierTest, ManyElements)
{
    Frontier frontier;

    for (int i = 0; i < 100; i++)
    {
        frontier.push(
        {
            "URL" + std::to_string(i),
            i
        });
    }

    EXPECT_EQ(frontier.size(), 100);

    for (int i = 0; i < 100; i++)
    {
        URLDepth item = frontier.pop();

        EXPECT_EQ(item.url, "URL" + std::to_string(i));
        EXPECT_EQ(item.depth, i);
    }

    EXPECT_TRUE(frontier.empty());
}

// ------------------------------------------------
// Multiple checkpoints
// ------------------------------------------------

TEST_F(FrontierTest, MultipleCheckpoints)
{
    Frontier frontier;

    frontier.push({"A", 0});
    frontier.checkpoint();

    frontier.push({"B", 1});
    frontier.checkpoint();

    Frontier recovered;

    EXPECT_EQ(recovered.size(), 2);

    EXPECT_EQ(recovered.pop().url, "A");
    EXPECT_EQ(recovered.pop().url, "B");
}