#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

#include <string>
#include <chrono>
#include <iostream>
#include <regex>

using namespace std::chrono_literals;

std::string test = "The quick brown fox jumps over the fallen tree";

std::string replace("bunny");
std::string search("fox");
boost::regex bre(search);
std::regex re(search);

int maxreps = 1000000;

using test_clock = std::chrono::steady_clock;

int measureTime(std::function<void()> algo) {
    auto start = test_clock::now();
    int reps = 0;

    while(test_clock::now() - start < 1000ms) {
        algo();
        reps++;
    }

    return reps;
}

double measureReps(std::function<void()> algo, int reps) {
    auto start = test_clock::now();
    while(reps > 0) {
        reps--;
        algo();
    }

     std::chrono::duration<double> diff = test_clock::now() - start;

     return diff.count();
}

int main(int argc, char** argv) {

    std::cout << "boost::replace_all:   " << measureTime([](){ auto str = boost::replace_all_copy(test, search, replace);}) << " reps/1s" << std::endl;
    std::cout << "boost::regex_replace: " << measureTime([](){ auto str = boost::regex_replace(test, bre, replace); }) << " reps/1s" << std::endl;
    std::cout << "std::regex_replace:   " << measureTime([](){ auto str = std::regex_replace(test, re, replace);}) << " reps/1s" << std::endl;

    std::cout << "boost::replace_all:   " << measureReps([](){ auto str = boost::replace_all_copy(test, search, replace);}, maxreps) << " seconds/" << maxreps << "reps" << std::endl;
    std::cout << "boost::regex_replace: " << measureReps([](){ auto str = boost::regex_replace(test, bre, replace); }, maxreps) << " seconds/" << maxreps << "reps" << std::endl;
    std::cout << "std::regex_replace:   " << measureReps([](){ auto str = std::regex_replace(test, re, replace);}, maxreps) << " seconds/" << maxreps << "reps" << std::endl;

    return 0;
}
