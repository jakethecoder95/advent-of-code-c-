#include "day4.h"
#include <cstddef>
#include <fstream>
#include <string>
#include <unordered_map>

int incMapValue(std::unordered_map<size_t, int> &map, size_t key, int amount) {

    if (map.find(key) == map.end()) {
        map.insert({ key, amount });
    } else {
        int value = map.find(key)->second;
        map[key] = value + amount;
    }

    return map.find(key)->second;
}

int day4Part1() {

    int total{0};
    std::ifstream file{ "./data/day4.txt" };
    std::string line{};

    size_t indexOfDivider{0};
    size_t indexOfStart{0};

    while (std::getline(file, line)) {

        // Get the index of the divider.
        if (indexOfDivider == 0 && indexOfStart == 0) {
            for (size_t i{0}; i < line.size(); i++) {
                char c = line.at(i);
                if (c == ':') {
                    indexOfStart = i + 2;
                } else if (line.at(i) == '|') {
                    indexOfDivider = i;
                }
            }
        }

        // Get winnings array.
        std::unordered_map<int, bool> winnings{};
        std::string winningsStr = line.substr(indexOfStart, indexOfDivider - indexOfStart - 1);
        for (size_t i{0}; i < winningsStr.size(); i+=3) {
            int num = std::stoi(winningsStr.substr(i, 2));
            winnings.insert({ num, true });
        }

        // Get my list
        int cardTotal{0};
        std::string myStr = line.substr(indexOfDivider+2, line.size() - indexOfDivider - 2);
        for (size_t i{0}; i < myStr.size(); i+=3) {
            int num = std::stoi(myStr.substr(i, 2));

            if (winnings.find(num) == winnings.end()) {
                continue;
            } else if (cardTotal == 0) {
                cardTotal = 1;
                continue;
            } else {
                cardTotal *= 2;
            }
        }
        total += cardTotal;
    }

    return total;
}

int day4Part2() {

    int total{0};
    std::ifstream file{ "./data/day4.txt" };
    std::string line{};

    size_t indexOfDivider{0};
    size_t indexOfStart{0};
    size_t index{0};

    std::unordered_map<size_t, int> cardCoppies{};

    while (std::getline(file, line)) {

        // Get the index of the divider.
        if (indexOfDivider == 0 && indexOfStart == 0) {
            for (size_t i{0}; i < line.size(); i++) {
                char c = line.at(i);
                if (c == ':') {
                    indexOfStart = i + 2;
                } else if (line.at(i) == '|') {
                    indexOfDivider = i;
                }
            }
        }

        // Get winnings array.
        std::unordered_map<int, bool> winnings{};
        std::string winningsStr = line.substr(indexOfStart, indexOfDivider - indexOfStart - 1);
        for (size_t i{0}; i < winningsStr.size(); i+=3) {
            int num = std::stoi(winningsStr.substr(i, 2));
            winnings.insert({ num, true });
        }

        // Initialize variables
        int cardValue = incMapValue(cardCoppies, index, 1);

        // Get the total amount of matches in the card
        int cardTotal{0};
        std::string myStr = line.substr(indexOfDivider+2, line.size() - indexOfDivider - 2);
        for (size_t i{0}; i < myStr.size(); i+=3) {
            int num = std::stoi(myStr.substr(i, 2));
            if (winnings.find(num) != winnings.end()) {
                cardTotal++;
            }
        }

        for (size_t i{index+1}; i <= index + (size_t)cardTotal; i++) {
            incMapValue(cardCoppies, i, cardValue);
        }

        total += cardValue;
        index++;
    }

    return total;
}
