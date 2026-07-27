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
    src/crawler.cpp
)

target_include_directories(crawler PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/../CodeQuotient/include
    ${PROJECT_SOURCE_DIR}/../CodeQuotient/src
)

target_link_libraries(crawler PRIVATE CURL::libcurl)

# ===========================
# Google Test
# ===========================

find_package(GTest REQUIRED)

# ===========================
# Test executable
# ===========================

enable_testing()

add_executable(crawler_tests
    tests/frontier_test.cpp
    tests/page_store_test.cpp
    tests/seen_store_test.cpp
    tests/url_normalizer_test.cpp
    tests/fetcher_test.cpp
    tests/crawler_test.cpp

    src/fetcher.cpp
    src/frontier.cpp
    src/pageStore.cpp
    src/seenStore.cpp
    src/urlNormalizer.cpp
    src/crawler.cpp
)

target_include_directories(crawler_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/../CodeQuotient/include
    ${PROJECT_SOURCE_DIR}/../CodeQuotient/src
)

target_link_libraries(crawler_tests PRIVATE
    CURL::libcurl
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(crawler_tests)