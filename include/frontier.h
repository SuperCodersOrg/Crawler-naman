#ifndef FRONTIER_H
#define FRONTIER_H

#include <string>
#include "../../CodeQuotient/include/queue.h"

struct URLDepth
{
    std::string url;
    int depth;
};

class Frontier
{
private:
    Queue<URLDepth> queue;

public:
    Frontier();
    Frontier(const Frontier& other);
    ~Frontier();

    Frontier& operator=(const Frontier& other);

    void push(const URLDepth& item);

    URLDepth pop();

    URLDepth front() const;

    bool empty() const;

    int size() const;
};

#endif