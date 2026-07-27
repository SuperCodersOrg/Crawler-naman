#include "frontier.h"
#include "../../CodeQuotient/include/queue.h"

#include <fstream>
#include <cstdio>

Frontier::Frontier()
    : storageFile("../storage/frontier.txt"),
      dirtyChanges(0)
{
    loadFromDisk();
}

Frontier::Frontier(const Frontier& other)
    : queue(other.queue),
      storageFile(other.storageFile),
      dirtyChanges(other.dirtyChanges)
{
}

Frontier::~Frontier()
{
}

Frontier& Frontier::operator=(const Frontier& other)
{
    if (this != &other)
    {
        queue = other.queue;
        storageFile = other.storageFile;
        dirtyChanges = other.dirtyChanges;
    }

    return *this;
}

void Frontier::push(const URLDepth& item)
{
    queue.enqueue(item);

    dirtyChanges++;

    if (dirtyChanges >= FLUSH_LIMIT)
    {
        flushToDisk();
        dirtyChanges = 0;
    }
}

URLDepth Frontier::pop()
{
    URLDepth item = queue.dequeue();

    dirtyChanges++;

    if (dirtyChanges >= FLUSH_LIMIT)
    {
        flushToDisk();
        dirtyChanges = 0;
    }

    return item;
}

URLDepth Frontier::front() const
{
    return queue.front();
}

bool Frontier::empty() const
{
    return queue.isEmpty();
}

int Frontier::size()
{
    return queue.size();
}

void Frontier::loadFromDisk()
{
    std::ifstream input(storageFile);

    if (!input.is_open())
    {
        return;
    }

    std::string url;
    int depth;

    while (input >> url >> depth)
    {
        queue.enqueue({url, depth});
    }

    input.close();
}

void Frontier::flushToDisk()
{
    std::ofstream output(storageFile, std::ios::trunc);

    if (!output.is_open())
    {
        return;
    }

    int count = queue.size();

    for (int i = 0; i < count; i++)
    {
        URLDepth item = queue.dequeue();

        output << item.url << " " << item.depth << '\n';

        queue.enqueue(item);
    }

    output.close();
}

void Frontier::clearDisk()
{
    std::remove(storageFile.c_str());
}

void Frontier::checkpoint()
{
    flushToDisk();
}