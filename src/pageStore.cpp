#include "pageStore.h"

#include <fstream>
#include <sstream>
#include <iostream>

PageStorage::PageStorage(const std::string& path)
{
    filePath = path;
    cachedCount = 0;
    initialized = false;
}

void PageStorage::initializeCount()
{
    if (initialized)
        return;

    std::ifstream file(filePath);

    if (!file.is_open())
    {
        initialized = true;
        cachedCount = 0;
        return;
    }

    cachedCount = 0;

    std::string line;

    while (getline(file, line))
    {
        if (line == "###PAGE###")
            cachedCount++;
    }

    initialized = true;
}

int PageStorage::pageCount()
{
    initializeCount();
    return cachedCount;
}

bool PageStorage::hasPage(const std::string& url)
{
    std::ifstream file(filePath);

    if (!file.is_open())
        return false;

    std::string line;

    while (getline(file, line))
    {
        if (line == "###PAGE###")
        {
            getline(file, line);

            if (line == "URL:" + url)
                return true;
        }
    }

    return false;
}

std::string PageStorage::getPage(const std::string& url)
{
    std::ifstream file(filePath);

    if (!file.is_open())
        return "";

    std::string line;

    while (getline(file, line))
    {
        if (line != "###PAGE###")
            continue;

        std::string currentURL;
        std::string html;

        getline(file, currentURL);

        std::string depth;
        getline(file, depth);

        getline(file, line);

        while (getline(file, line))
        {
            if (line == "###ENDHTML###")
                break;

            html += line;
            html += '\n';
        }

        if (currentURL == "URL:" + url)
            return html;
    }

    return "";
}

void PageStorage::storePage(const std::string& url,const std::string& html,int depth)
{
    if (url.empty())
        return;

    std::ifstream input(filePath);

    std::stringstream buffer;

    bool found = false;

    if (input.is_open())
    {
        std::string line;

        while (getline(input, line))
        {
            if (line != "###PAGE###")
            {
                buffer << line << '\n';
                continue;
            }

            std::string pageStart = line;

            std::string currentURL;
            getline(input, currentURL);

            std::string currentDepth;
            getline(input, currentDepth);

            getline(input, line);

            std::string htmlData;

            while (getline(input, line))
            {
                if (line == "###ENDHTML###")
                    break;

                htmlData += line;
                htmlData += '\n';
            }

            if (currentURL == "URL:" + url)
            {
                found = true;

                buffer << "###PAGE###\n";
                buffer << "URL:" << url << "\n";
                buffer << "DEPTH:" << depth << "\n";
                buffer << "HTML\n";
                buffer << html;
                if (html.empty() || html.back() != '\n')
                    buffer << '\n';
                buffer << "###ENDHTML###\n";
            }
            else
            {
                buffer << "###PAGE###\n";
                buffer << currentURL << "\n";
                buffer << currentDepth << "\n";
                buffer << "HTML\n";
                buffer << htmlData;
                buffer << "###ENDHTML###\n";
            }
        }

        input.close();
    }

    if (!found)
    {
        buffer << "###PAGE###\n";
        buffer << "URL:" << url << "\n";
        buffer << "DEPTH:" << depth << "\n";
        buffer << "HTML\n";
        buffer << html;
        if (html.empty() || html.back() != '\n')
            buffer << '\n';
        buffer << "###ENDHTML###\n";

        initializeCount();
        cachedCount++;
    }

    std::ofstream output(filePath);

    if (!output.is_open())
    {
        std::cerr << "Unable to open storage file.\n";
        return;
    }

    output << buffer.str();
}