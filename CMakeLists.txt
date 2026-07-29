cmake_minimum_required(VERSION 3.16)

project(Crawler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)

# Main executable
add_executable(crawler
    main.cpp

    src/crawler.cpp
    src/fetcher.cpp
    src/frontier.cpp
    src/pageStore.cpp
    src/seenStore.cpp
    src/urlNormalizer.cpp
    src/htmlParser.cpp
    src/tokenizer.cpp
    src/wordNormalizer.cpp
    src/indexStorage.cpp
    src/indexer.cpp
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

enable_testing()

add_executable(crawler_tests
    # Test Files
    tests/frontier_test.cpp
    tests/page_store_test.cpp
    tests/seen_store_test.cpp
    tests/url_normalizer_test.cpp
    tests/fetcher_test.cpp
    tests/crawler_test.cpp
    tests/html_parser_test.cpp
    tests/tokenizer_test.cpp
    tests/word_normalizer_test.cpp
    tests/indexer_storage_test.cpp
    tests/indexer_test.cpp

    # Source Files
    src/frontier.cpp
    src/pageStore.cpp
    src/seenStore.cpp
    src/urlNormalizer.cpp
    src/fetcher.cpp
    src/crawler.cpp
    src/htmlParser.cpp
    src/tokenizer.cpp
    src/wordNormalizer.cpp
    src/indexStorage.cpp
    src/indexer.cpp
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