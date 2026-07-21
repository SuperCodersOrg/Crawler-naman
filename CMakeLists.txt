cmake_minimum_required(VERSION 3.16)

project(Crawler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)

add_executable(crawler
    main.cpp

    src/fetcher.cpp
    src/frontier.cpp
    src/pageStore.cpp
    src/seenStore.cpp
    src/urlNormalizer.cpp
)

target_include_directories(crawler PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/../CodeQuotient/include
    ${PROJECT_SOURCE_DIR}/../CodeQuotient/src
)

target_link_libraries(crawler PRIVATE CURL::libcurl)