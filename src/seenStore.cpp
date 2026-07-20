#include "seenStore.h"
#include "../../CodeQuotient/include/hashmap.h"

bool SeenStore::contains(const std::string& url) {
    if (url.empty()) {
        return false;
    }

    return seenURLs.exists(url);
}

void SeenStore::insert(const std::string& url) {
    if (url.empty()) {
        return;
    }

    if (!seenURLs.exists(url)) {
        seenURLs.set(url, true);
    }
}

int SeenStore::count() {
    return seenURLs.getSize();
}