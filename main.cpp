#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

#include <string>
#include <chrono>
#include <iostream>
#include <regex>

using namespace std::chrono_literals;

int main(int argc, char** argv) {

    std::string test = "The quick brown fox jumps over the fallen tree";

    auto start = std::chrono::high_resolution_clock::now();

    int64_t reps = 0;

    while(reps < 1000000) {
        auto result = boost::replace_all_copy(test, "fox", "bunny");
        reps++;
    }

    std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;

    std::cout << "boost::replace_all:   " << diff.count() << std::endl;

    reps = 0;
    start = std::chrono::high_resolution_clock::now();
    boost::regex bre("fox");

    while(reps < 1000000) {
        auto result = boost::regex_replace(test, bre, "bunny");
        reps++;
    }

    diff = std::chrono::high_resolution_clock::now() - start;
    std::cout << "boost::regex_replace: " << diff.count() << std::endl;

    std::regex re("fox");
    reps = 0;
    start = std::chrono::high_resolution_clock::now();


    while(reps < 1000000) {
        auto result = std::regex_replace(test, re, "bunny");
        reps++;
    }

    diff = std::chrono::high_resolution_clock::now() - start;
    std::cout << "std::regex_replace:   " << diff.count() << std::endl;

    std::cout << test << std::endl;

    return 0;
}
