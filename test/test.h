#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <algorithm>
#include <vector>

#define ASSERT(T) \
    if (!(T)) { \
    std::cerr << "Assert faild on line: " << __LINE__ << " : (" << #T << ")" << std::endl; \
    exit(1); \
    }

#define START()  \
    typedef std::chrono::high_resolution_clock clock_; \
    typedef std::chrono::duration<double, std::ratio<1> > second_; \
    auto _start_time = clock_::now();

#define PASSED() \
    std::cerr << std::endl \
              << "All tests PASSED in: " \
              << std::chrono::duration_cast<second_>(clock_::now() - _start_time).count() \
              << "s" << std::endl; \
    exit(0);

#define RUN_TEST(name) \
    do{ \
        auto _test_start_time = clock_::now(); \
        /*std::cout << "Running test " << #name << "..." << std::endl;*/ \
        test_##name(); \
        std::cerr << " * Test passed: "  \
                  << #name << " in: " \
                  << std::chrono::duration_cast<second_>(clock_::now() - _test_start_time).count() \
                  << "s" << std::endl; \
    } while (false)

void print(std::vector<std::string> tokens){
    std::cout << "==== TOKENS ====" << std::endl;
    for (std::string t : tokens) {
        std::cout << "\"" << t << "\" ";
    }
    std::cout << "================" << std::endl;
}

void print(std::string title, std::string text){
    std::cout << "==== " + title + " ====" << std::endl
              << text << std::endl
              << "================" << std::endl;
}

#endif // TEST_H
