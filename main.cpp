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

    while(std::chrono::high_resolution_clock::now() - start < 1000ms) {
        auto result = boost::replace_all_copy(test, "fox", "bunny");
        reps++;
    }

    std::cout << "boost::replace_all:   " << reps << std::endl;

    reps = 0;
    start = std::chrono::high_resolution_clock::now();
    boost::regex bre("fox");

    while(std::chrono::high_resolution_clock::now() - start < 1000ms) {
        auto result = boost::regex_replace(test, bre, "bunny");
        reps++;
    }

    std::cout << "boost::regex_replace: " << reps << std::endl;

    std::regex re("fox");
    reps = 0;
    start = std::chrono::high_resolution_clock::now();


    while(std::chrono::high_resolution_clock::now() - start < 1000ms) {
        auto result = std::regex_replace(test, re, "bunny");
        reps++;
    }

    std::cout << "std::regex_replace:   " << reps << std::endl;

    std::cout << test << std::endl;

    return 0;
}
