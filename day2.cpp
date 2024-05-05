#include <cstddef>
#include <fstream>
#include <string>
#include <unordered_map>

#include "day2.h"

const std::unordered_map<char, int> numbersMap = {
    { '0', 0 },
    { '1', 1 },
    { '2', 2 },
    { '3', 3 },
    { '4', 4 },
    { '5', 5 },
    { '6', 6 },
    { '7', 7 },
    { '8', 8 },
    { '9', 9 }
};

struct Colors {
    int red;
    int green;
    int blue;
};

int getMinRocksFor(std::string line, std::string color) {
    int minimum{1};

    std::size_t pos{0};
    while (pos != std::string::npos && pos < line.length()) {
        pos = line.find(color, pos);
        if (pos == std::string::npos) {
            continue;
        }

        std::size_t posOfNum = pos - 2;
        std::string strvalue{};
        while (numbersMap.find(line.at(posOfNum)) != numbersMap.end()) {
            strvalue.insert(0, 1, numbersMap.find(line.at(posOfNum))->first);
            --posOfNum;
        }

        int value = std::stoi(strvalue);
        if (value > minimum) {
            minimum = value;
        }

        pos += color.length();
    }

    return minimum;
};


bool gameIsPossible(std::string line, std::string color, int limit) {
    std::size_t pos{0};
    while (pos != std::string::npos && pos < line.length()) {

        pos = line.find(color, pos);
        if (pos == std::string::npos) {
            continue;
        }

        std::size_t posOfNum = pos - 2;
        std::string strvalue{};
        while (numbersMap.find(line.at(posOfNum)) != numbersMap.end()) {
            strvalue.insert(0, 1, numbersMap.find(line.at(posOfNum))->first);
            --posOfNum;
        }

        bool exceedsLimit = std::stoi(strvalue) > limit;
        if (exceedsLimit) {
            return false;
        }

        pos += color.length();
    }

    return true;
};

int day2Part1() {

    int total{0};

    std::ifstream day1txt{ "./data/day2.txt" };
    std::string line{};
    std::size_t index{0};

    while (std::getline(day1txt, line)) {

        Colors bagColors;
        bagColors.red = 12;
        bagColors.green = 13;
        bagColors.blue = 14;

        bool totalRed = gameIsPossible(line, "red", bagColors.red);
        bool totalGreen = gameIsPossible(line, "green", bagColors.green);
        bool totalBlue = gameIsPossible(line, "blue", bagColors.blue);

        if (totalRed && totalGreen && totalBlue) {
            total += index+1;
        }

        index++;
    }

    return total;
}

int day2Part2() {

    int total{0};

    std::ifstream day1txt{ "./data/day2.txt" };
    std::string line{};

    while (std::getline(day1txt, line)) {

        int minRed{getMinRocksFor(line, "red")};
        int minGreen{getMinRocksFor(line, "green")};
        int minBlue{getMinRocksFor(line, "blue")};

        int power = minRed * minBlue * minGreen;
        total += power;
    }

    return total;
}
