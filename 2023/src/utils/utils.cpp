#include "utils.h"

#include <vector>

std::vector<int> extractIntsFrom(std::string val) {

  std::vector<int> numbers{};

  std::string num{};
  for (size_t i{0}; i < val.length(); i++) {
    char c = val.at(i);
    if (c != ' ') {
      num.push_back(c);
    }
    if ((c == ' ' || i == val.length() - 1) && num.length() > 0) {
      numbers.push_back(std::stoi(num));
      num.clear();
    }
  }

  return numbers;
}

std::vector<long> extractLongsFrom(std::string val) {

  std::vector<long> numbers{};

  std::string num{};
  for (size_t i{0}; i < val.length(); i++) {
    char c = val.at(i);
    if (c != ' ') {
      num.push_back(c);
    }
    if ((c == ' ' || i == val.length() - 1) && num.length() > 0) {
      numbers.push_back(std::stol(num));
      num.clear();
    }
  }

  return numbers;
}
