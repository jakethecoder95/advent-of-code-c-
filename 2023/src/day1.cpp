#include <cctype>
#include <fstream>
#include <string>
#include <unordered_map>

#include "day1.h"

const std::unordered_map<std::string, char> numbersMap = {
    { "one", '1' },
    { "two", '2' },
    { "three", '3' },
    { "four", '4' },
    { "five", '5' },
    { "six", '6' },
    { "seven", '7' },
    { "eight", '8' },
    { "nine", '9' }
};

int day1Part1() {
    std::ifstream day1txt{ "./data/day1.txt" };
    int total = 0;
    std::string line{};

    while (std::getline(day1txt, line)) {

        std::string num{};

        for (std::string::size_type i = 0; i < line.size(); i++) {
            char digit = line.at(i);
            if (!std::isdigit(digit)) {
                continue;
            }

            if (num.length() == 0) {
                num.insert(0, 1, digit);
            } else {
                num.replace(1, 1, 1, digit);
            }
        }

        if (num.length() == 1) {
            num.replace(1, 1, 1, num.at(0));
        }

        total += std::stoi(num);
    }

    return total;
}

int day1Part2() {
    std::ifstream day1txt{ "./data/day1.txt" };
    int total = 0;
    std::string line{};

    while (std::getline(day1txt, line)) {

        std::string num{};

        for (std::string::size_type i = 0; i < line.size(); i++) {
            char digit = line.at(i);

            if (i >= 2) {
                std::string prev3 = line.substr(i-2, 3);
                if (auto value = numbersMap.find(prev3); value != numbersMap.end()) {
                    digit = value->second;
                }
            }
            if (i >= 3) {
                std::string prev4 = line.substr(i-3, 4);
                if (auto value = numbersMap.find(prev4); value != numbersMap.end()) {
                    digit = value->second;
                }
            }
            if (i >= 4) {
                std::string prev5 = line.substr(i-4, 5);
                if (auto value = numbersMap.find(prev5); value != numbersMap.end()) {
                    digit = value->second;
                }
            }

            if (!std::isdigit(digit)) {
                continue;
            }

            if (num.length() == 0) {
                num.insert(0, 1, digit);
            } else {
                num.replace(1, 1, 1, digit);
            }
        }

        if (num.length() == 1) {
            num.replace(1, 1, 1, num.at(0));
        }

        total += std::stoi(num);
    }

    return total;
}
