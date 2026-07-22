#ifndef SEENSTORE_H
#define SEENSTORE_H

#include <string>
#include "../../CodeQuotient/include/hashmap.h"

class SeenStore {
public:
    bool contains(const std::string& url) ;
    void insert(const std::string& url);
    int count() ;

private:
    HashMap<std::string, bool> seenURLs;
};

#endif