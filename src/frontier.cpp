#include "frontier.h"
#include "../../CodeQuotient/include/queue.h"

Frontier::Frontier()
{
}

Frontier::Frontier(const Frontier& other)
    : queue(other.queue)
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
    }

    return *this;
}

void Frontier::push(const URLDepth& item)
{
    queue.enqueue(item);
}

URLDepth Frontier::pop()
{
    return queue.dequeue();
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