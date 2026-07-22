#include "pageStore.h"

#include <fstream>
#include <iostream>

PageStorage::PageStorage(const std::string& path)
{
    filePath = path;
    cachedCount = 0;
    initialized = false;

    buildIndex();
}

void PageStorage::buildIndex()
{
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        initialized = true;
        return;
    }

    std::string line;

    while (true)
    {
        std::streampos offset = file.tellg();

        if (!getline(file, line))
            break;

        if (line != "###PAGE###")
            continue;

        std::string urlLine;
        getline(file, urlLine);

        std::string depthLine;
        getline(file, depthLine);

        getline(file, line);      // HTML

        std::string url = urlLine.substr(4);

        pageIndex.set(url, offset);

        cachedCount++;

        while (getline(file, line))
        {
            if (line == "###ENDHTML###")
                break;
        }
    }

    initialized = true;
}

int PageStorage::pageCount()
{
    return cachedCount;
}

bool PageStorage::hasPage(const std::string& url)
{
    return pageIndex.exists(url);
}

void PageStorage::storePage(const std::string& url,
                            const std::string& html,
                            int depth)
{
    if (url.empty())
        return;

    bool alreadyExists = pageIndex.exists(url);

    std::ofstream output(filePath, std::ios::app);

    if (!output.is_open())
    {
        std::cerr << "Unable to open storage file.\n";
        return;
    }

    std::streampos offset = output.tellp();

    pageIndex.set(url, offset);

    output << "###PAGE###\n";
    output << "URL:" << url << '\n';
    output << "DEPTH:" << depth << '\n';
    output << "HTML\n";
    output << html;

    if (html.empty() || html.back() != '\n')
        output << '\n';

    output << "###ENDHTML###\n";

    if (!alreadyExists)
        cachedCount++;
}

std::string PageStorage::getPage(const std::string& url)
{
    if (!pageIndex.exists(url))
        return "";

    std::streampos offset = pageIndex.get(url);

    std::ifstream input(filePath);

    if (!input.is_open())
        return "";

    input.seekg(offset);

    std::string line;

    getline(input, line);   // ###PAGE###
    getline(input, line);   // URL
    getline(input, line);   // DEPTH
    getline(input, line);   // HTML

    std::string html;

    while (getline(input, line))
    {
        if (line == "###ENDHTML###")
            break;

        html += line;
        html += '\n';
    }

    return html;
}