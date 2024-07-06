#include "day5.h"
#include "./utils/utils.h"

#include <climits>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct Map {
  long destLow;
  long destHigh;
  long sourceLow;
  long sourceHigh;
  long range;
};

const bool SHOULD_LOG = false;

const std::unordered_map<size_t, std::string> INDEX_NAME_MAP{
    {0, "Soil"},        {1, "Fertilizer"}, {2, "Water"},   {3, "Light"},
    {4, "Temperature"}, {5, "Humidity"},   {6, "Location"}};

void logRange(std::string prefix, Map range) {
  if (SHOULD_LOG) {
    std::cout << prefix << range.sourceLow << "-" << range.sourceHigh << " to "
              << range.destLow << "-" << range.destHigh << '\n';
  }
}

void addOrReplaceMap(Map newRange, std::vector<Map> &ranges, bool useDest) {

  bool wasAdded{false};

  for (size_t i{0}; i < ranges.size(); i++) {

    Map curRange{ranges.at(i)};

    if (useDest && curRange.destLow == newRange.destLow) {
      ranges[i] = newRange;
      wasAdded = true;
      break;
    } else if (!useDest && curRange.destLow == newRange.sourceLow) {
      ranges[i] = newRange;
      wasAdded = true;
      break;
    }
  }

  if (!wasAdded) {
    ranges.push_back(newRange);
  }
}

std::vector<Map> performMapping(std::vector<Map> ranges,
                                std::vector<std::vector<Map>> collections,
                                size_t collectionIndex) {

  if (collectionIndex == collections.size()) {
    return ranges;
  }

  std::vector<Map> newRanges{};

  for (Map range : ranges) {
    logRange("Range: ", range);

    std::vector collection = collections.at(collectionIndex);
    for (Map map : collection) {

      logRange("Current Map: ", map);

      // Handle out of range.
      if (range.destHigh < map.sourceLow || range.destLow > map.sourceHigh) {
        logRange("Out of Range: ", map);
        addOrReplaceMap(range, newRanges, true);
        continue;
      }

      // Handle partial out of range.
      if (range.destLow < map.sourceLow && (range.destHigh >= map.sourceLow &&
                                            range.destHigh <= map.sourceHigh)) {
        Map overlapMap{};
        overlapMap.destLow = range.destLow;
        overlapMap.destHigh = map.sourceLow - 1;
        newRanges.push_back(overlapMap);
        logRange("Partial Out of Range Low: ", overlapMap);
        range.destLow = map.sourceLow;
      }
      if (range.destHigh > map.sourceHigh &&
          (range.destLow <= map.sourceHigh && range.destLow >= map.sourceLow)) {

        Map overlapMap{};
        overlapMap.destLow = map.sourceHigh + 1;
        overlapMap.destHigh = range.destHigh;
        newRanges.push_back(overlapMap);
        logRange("Partial Out of Range High: ", overlapMap);
        range.destHigh = map.sourceHigh;
      }

      // Handle in range
      Map inRangeMap{};
      inRangeMap.destLow = map.destLow + (range.destLow - map.sourceLow);
      inRangeMap.destHigh = map.destHigh - (map.sourceHigh - range.destHigh);
      inRangeMap.sourceLow = range.destLow;
      inRangeMap.sourceHigh = range.destHigh;

      addOrReplaceMap(inRangeMap, newRanges, false);
      logRange("In Range: ", inRangeMap);
      break;
    }
  }

  return performMapping(newRanges, collections, collectionIndex + 1);
}

void getSeedsAndMappingsFromFile(
    std::vector<long> &seeds,
    std::vector<std::vector<Map>> &mapping_collections) {

  std::string line{};
  std::ifstream file{"./data/day5.txt"};

  while (std::getline(file, line)) {

    // Skip empty lines.
    if (line.empty()) {
      continue;
    }

    // Get the seeds out of the first line.
    if (line.substr(0, 5) == "seeds") {
      std::string seedstr = line.substr(7, 8 - line.length());
      seeds = extractLongsFrom(seedstr);
      continue;
    }

    // Check if line is the start of a new map.
    if (line.at(line.length() - 1) == ':') {
      mapping_collections.push_back({});
      continue;
    }

    // Handle mapping line.
    std::vector<long> lineValues = extractLongsFrom(line);

    Map map{};
    map.destLow = lineValues.at(0);
    map.destHigh = lineValues.at(0) + (lineValues.at(2) - 1);
    map.sourceLow = lineValues.at(1);
    map.sourceHigh = lineValues.at(1) + (lineValues.at(2) - 1);
    map.range = lineValues.at(2);

    mapping_collections.at(mapping_collections.size() - 1).push_back(map);
  }
}

long day5Part1() {

  std::vector<long> seeds{};
  std::vector<std::vector<Map>> mapping_collections{};
  getSeedsAndMappingsFromFile(seeds, mapping_collections);

  long closest_location = LONG_MAX;
  for (long seed : seeds) {
    long next{seed};
    for (std::vector collection : mapping_collections) {
      for (Map map : collection) {
        if (next >= map.sourceLow && next <= map.sourceHigh) {
          long diff = next - map.sourceLow;
          next = map.destLow + diff;
          break;
        }
      }
    }
    if (next < closest_location) {
      closest_location = next;
    }
  }

  return closest_location;
}

long day5Part2() {

  std::vector<long> seeds{};
  std::vector<std::vector<Map>> mappingCollections{};
  getSeedsAndMappingsFromFile(seeds, mappingCollections);

  std::unordered_map<size_t, std::vector<Map>> seedToRangeMap{};

  std::vector<Map> seedRanges{};
  for (size_t i{0}; i < seeds.size() - 1; i += 2) {

    long seedStart{seeds.at(i)};
    long seedEnd{seeds.at(i) + (seeds.at(i + 1) - 1)};

    Map range{};
    range.destLow = seedStart;
    range.destHigh = seedEnd;

    seedRanges.push_back(range);
  }

  std::vector<Map> resultRanges{
      performMapping(seedRanges, mappingCollections, 0)};

  long closest_location = LONG_MAX;
  for (Map range : resultRanges) {
    closest_location =
        range.destLow < closest_location ? range.destLow : closest_location;
  }

  return closest_location;
}
