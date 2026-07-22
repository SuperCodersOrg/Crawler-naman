#include <fetcher.h>
#include <string>

std::string Fetcher::fetch(const std::string& url)
{
    CURL* curl = curl_easy_init();

    if (curl == nullptr)
        return "";

    std::string html;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

    curl_easy_setopt(
        curl,
        CURLOPT_USERAGENT,
        "CodeQuotientCrawler/1.0 (namanaggarwal98124@gmail.com)"
    );

    CURLcode result = curl_easy_perform(curl);

    long responseCode = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);

    curl_easy_cleanup(curl);

    if (result != CURLE_OK || responseCode != 200)
        return "";

    return html;
}

size_t Fetcher::writeCallback(void* contents,size_t size,size_t nmemb,void* userp)
{
    size_t totalBytes = size * nmemb;

    std::string* html = static_cast<std::string*>(userp);
    html->append(static_cast<char*>(contents), totalBytes);

    return totalBytes;
}