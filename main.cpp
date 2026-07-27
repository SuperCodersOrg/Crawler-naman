#include <iostream>
#include "frontier.h"

int main()
{
    {
        std::cout << "========== First Run ==========\n";

        Frontier frontier;

        frontier.push({"https://google.com", 0});
        frontier.push({"https://github.com", 1});
        frontier.push({"https://stackoverflow.com", 2});

        std::cout << "Queue Size : " << frontier.size() << "\n";

        std::cout << "Front : "
                  << frontier.front().url
                  << " "
                  << frontier.front().depth
                  << "\n";

        std::cout << "Popped : "
                  << frontier.pop().url
                  << "\n";

        std::cout << "Remaining Size : "
                  << frontier.size()
                  << "\n";

        // Force persistence
        for (int i = 0; i < 100; i++)
        {
            frontier.push({"https://example.com/" + std::to_string(i), i});
            frontier.pop();
        }

        std::cout << "Checkpoint written.\n";
    }

    std::cout << "\n========== Simulating Restart ==========\n";

    {
        Frontier frontier;

        std::cout << "Recovered Queue Size : "
                  << frontier.size()
                  << "\n";

        while (!frontier.empty())
        {
            URLDepth page = frontier.pop();

            std::cout << page.url
                      << " "
                      << page.depth
                      << "\n";
        }

        frontier.clearDisk();
    }

    std::cout << "\nPersistence file deleted.\n";

    return 0;
}