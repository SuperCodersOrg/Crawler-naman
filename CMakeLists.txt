cmake_minimum_required(VERSION 3.20)
project(Fetcher)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)

include_directories(include)

add_library(fetcher
    src/fetcher.cpp
    src/frontier.cpp
    src/seenStore.cpp
    ../../CodeQuotient/src/hashmap.tpp
    ../../CodeQuotient/src/queue.tpp
)

target_link_libraries(fetcher
    CURL::libcurl
)

add_executable(main
    main.cpp
)

target_link_libraries(testFetcher
    fetcher
)