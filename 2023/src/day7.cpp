#include "./day7.h"
#include "./utils/utils.h"

#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>

enum HandScore {
  FIVE_KIND = 7,
  FOUR_KIND = 6,
  FULL_HOUSE = 5,
  THREE_KIND = 4,
  TWO_PAIR = 3,
  ONE_PAIR = 2,
  HIGH_CARD = 1
};

const std::unordered_map<char, int> CARD_SCORES{
    {'A', 14}, {'K', 13}, {'Q', 12}, {'J', 11}, {'T', 10}, {'9', 9}, {'8', 8},
    {'7', 7},  {'6', 6},  {'5', 5},  {'4', 4},  {'3', 3},  {'2', 2},
};

enum HandScore getCardCountMap(std::string hand) {

  std::unordered_map<char, int> charToCountMap{};
  for (char card : hand) {
    if (charToCountMap.find(card) == charToCountMap.end()) {
      charToCountMap.insert({card, 1});
    } else {
      charToCountMap[card] = charToCountMap.find(card)->second + 1;
    }
  }

  if (charToCountMap.size() == 1) {
    return HandScore::FIVE_KIND;
  }

  if (charToCountMap.size() == 2) {
    auto first{charToCountMap.begin()};
    return first->second == 3 || first->second == 2 ? HandScore::FULL_HOUSE
                                                    : HandScore::FOUR_KIND;
  }

  if (charToCountMap.size() == 4) {
    return HandScore::ONE_PAIR;
  }

  if (charToCountMap.size() == 5) {
    return HandScore::HIGH_CARD;
  }

  auto it = charToCountMap.begin();
  int first{it->second};
  std::advance(it, 1);
  int second{it->second};
  std::advance(it, 1);
  int third{it->second};

  if (first == 2 || second == 2 || third == 2) {
    return TWO_PAIR;
  }

  return THREE_KIND;
}

bool compareHands(std::string hand1, std::string hand2) {

  // Get hand scores.
  enum HandScore hand1Score { getCardCountMap(hand1) };
  enum HandScore hand2Score { getCardCountMap(hand2) };

  if (hand1Score != hand2Score) {
    return hand1Score < hand2Score;
  }

  // Resovle hand scores equal.
  size_t index{0};
  char hand1Card{hand1.at(index)};
  char hand2Card{hand2.at(index)};

  while (CARD_SCORES.find(hand1Card)->second ==
         CARD_SCORES.find(hand2Card)->second) {
    index++;
    hand1Card = hand1.at(index);
    hand2Card = hand2.at(index);
  }

  return CARD_SCORES.find(hand1Card)->second <
         CARD_SCORES.find(hand2Card)->second;
}

int day7Part1() {
  int result{0};

  std::string line{};
  std::ifstream file{"./data/day7.txt"};

  std::vector<int> bids{};
  std::vector<std::string> hands{};

  while (std::getline(file, line)) {
    hands.push_back(line.substr(0, 5));
    bids.push_back(std::stoi(line.substr(6, line.length() - 6)));
  }

  std::vector handsCpy = hands;
  std::sort(handsCpy.begin(), handsCpy.end(), compareHands);

  for (size_t i{0}; i < bids.size(); i++) {
    int bid{bids.at(i)};
    std::string hand{hands.at(i)};
    ptrdiff_t pos =
        std::find(handsCpy.begin(), handsCpy.end(), hand) - handsCpy.begin();
    int rank = (int)pos + 1;
    result += bid * rank;
  }

  return result;
}

int day7Part2() {
  int result{0};
  return result;
}
