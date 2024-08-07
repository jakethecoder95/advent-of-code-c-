#include "./day6.h"
#include "./utils/utils.h"

#include <fstream>
#include <string>
#include <vector>

int day6Part1() {

  int result{1};

  std::string line{};
  std::ifstream file{"./data/day6.txt"};

  std::vector<int> times;
  std::vector<int> distances;

  while (std::getline(file, line)) {
    if (line.at(0) == 'T') {
      times = extractIntsFrom(line.substr(11, line.length() - 1));
    } else {
      distances = extractIntsFrom(line.substr(11, line.length() - 1));
    }
  }

  for (size_t i{0}; i < times.size(); i++) {
    int time{times.at(i)};
    int distance{distances.at(i)};

    int half{time / 2};
    int prevLow{0};
    int prevHigh{time};

    while (half > 0) {

      if (half == prevHigh) {
        break;
      }

      int nextHalf{0};
      if (half * (time - half) > distance) {
        prevHigh = half;
        nextHalf = half - ((half - prevLow) / 2);
      } else {
        nextHalf = half + ((prevHigh - half) / 2);
        prevLow = half;
      }

      if (nextHalf == half || nextHalf == prevLow || nextHalf == prevHigh) {
        half = 0;
      } else {
        half = nextHalf;
      }
    }

    int value = (((time / 2) - prevHigh) * 2) + 1 +time % 2;
    result *= value;
  }

  return result;
}

long long day6Part2() {

  std::string line{};
  std::ifstream file{"./data/day6.txt"};

  std::vector<int> times;
  std::vector<int> distances;

  while (std::getline(file, line)) {
    if (line.at(0) == 'T') {
      times = extractIntsFrom(line.substr(11, line.length() - 1));
    } else {
      distances = extractIntsFrom(line.substr(11, line.length() - 1));
    }
  }

  std::string timestr{};
  std::string distancestr{};

  for (size_t i{0}; i < times.size(); i++) {
    timestr.append(std::to_string(times.at(i)));
    distancestr.append(std::to_string(distances.at(i)));
  }

  long long time{std::stoll(timestr)};
  long long distance{std::stoll(distancestr)};

  long long half{time / 2};
  long long prevLow{0};
  long long prevHigh{time};

  while (half > 0) {

    if (half == prevHigh) {
      break;
    }

    long long nextHalf{0};
    if (half * (time - half) > distance) {
      prevHigh = half;
      nextHalf = half - ((half - prevLow) / 2);
    } else {
      nextHalf = half + ((prevHigh - half) / 2);
      prevLow = half;
    }

    if (nextHalf == half || nextHalf == prevLow || nextHalf == prevHigh) {
      half = 0;
    } else {
      half = nextHalf;
    }
  }

  return (((time / 2) - prevHigh) * 2) + 1 +time % 2;
}
