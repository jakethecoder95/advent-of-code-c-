#include <cstddef>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "day3.h"

const std::unordered_map<char, bool> numbers{
    {'0', true},
    {'1', true},
    {'2', true},
    {'3', true},
    {'4', true},
    {'5', true},
    {'6', true},
    {'7', true},
    {'8', true},
    {'9', true},
};

bool is_number(char c) {
   return numbers.find(c) != numbers.end();
}

bool check_line_at(std::string line, size_t i) {
    if (line.at(i) != '.' && !is_number(line.at(i))) {
        return false;
    }
    if (i > 0 && line.at(i-1) != '.' && !is_number(line.at(i-1))) {
        return false;
    }
    if (i < line.length() - 1 && line.at(i+1) != '.' && !is_number(line.at(i+1))) {
        return false;
    }

    return true;
}

bool check_edge_has_special_char(std::string line, size_t start, size_t end) {
    for (size_t i = start; i <= end; i++) {
        if (line.at(i) != '.' && !is_number(line.at(i))) {
            return true;
        }
    }
    return false;
}

std::pair<size_t, size_t> find_coordinate(
    std::vector<std::pair<size_t, size_t>> coors,
    size_t index
) {
    for (std::pair coor : coors) {
        if (coor.first <= index && coor.second >= index) {
            return coor;
        }
    }
    throw;
}

int day3Part1() {
    int total{0};

    std::ifstream file{ "./data/day3.txt" };
    std::string line{};
    std::vector<std::string> graph{};

    while (std::getline(file, line)) {
        graph.push_back(line);
    }

    for (size_t i{0}; i < graph.size(); i++) {
        std::string cur_line = graph[i];

        for (size_t j{0}; j < cur_line.length(); j++) {
            char c = cur_line.at(j);

            if (!is_number(c)) {
                continue;
            }

            size_t start = j;
            std::string number{cur_line.at(j)};
            while (j+1 < cur_line.length() && is_number(cur_line.at(j+1))) {
                number.push_back(cur_line.at(++j));
            }
            size_t end = j;

            size_t edge_start;
            if (start > 0) {
                edge_start = start - 1;
            } else {
                edge_start = start;
            }

            size_t edge_end;
            if (end < cur_line.length() - 1) {
                edge_end = end + 1;
            } else {
                edge_end = end;
            }

            bool is_part_num{false};

            // Check sides
            is_part_num = check_edge_has_special_char(cur_line, edge_start, edge_end);

            // Check above
            if (i > 0 && !is_part_num) {
                is_part_num = check_edge_has_special_char(graph[i-1], edge_start, edge_end);
            }

            // Check below
            if (i < graph.size() - 1 && !is_part_num) {
                is_part_num = check_edge_has_special_char(graph[i+1], edge_start, edge_end);
            }

            if (is_part_num) {
                total += std::stoi(number);
            }
        }
    }

    return total;
}

int day3Part2() {
    int total{0};

    std::ifstream file{ "./data/day3.txt" };

    std::string line{};
    size_t linenum{0};

    std::vector<std::vector<std::pair<size_t, size_t>>> coordinates{};
    std::vector<std::string> graph{};

    while (std::getline(file, line)) {
        graph.push_back(line);

        for (size_t i{0}; i < line.length(); i++) {
            coordinates.push_back(std::vector<std::pair<size_t, size_t>>());
            char c = line.at(i);

            if (!is_number(c)) {
                continue;
            }

            size_t start = i;
            std::string number{line.at(i)};
            while (i+1 < line.length() && is_number(line.at(i+1))) {
                number.push_back(line.at(++i));
            }
            size_t end = i;

            coordinates[linenum].push_back({start, end});
        }

        linenum++;
    }

    for (size_t i{0}; i < graph.size(); i++) {
        std::string cur_line = graph[i];

        for (size_t j{0}; j < cur_line.length(); j++) {
            char c = cur_line.at(j);

            if (c != '*') {
                continue;
            }

            std::vector<std::pair<size_t, size_t>> connected_nums{};

            size_t start_line{i == 0 ? 0 : i-1};
            size_t end_line{i == graph.size() ? i : i+1};

            for (size_t lnum{start_line}; lnum <= end_line; lnum++) {

                size_t start_char = j == 0 ? j : j-1;
                size_t end_char = j == cur_line.size() - 1 ? j : j+1;

                for (size_t cnum{start_char}; cnum <= end_char; cnum++) {
                    if (is_number(graph[lnum][cnum])) {
                        connected_nums.push_back({lnum, cnum});
                        if (cnum < end_char && is_number(graph[lnum][++cnum])) {
                            break;
                        }
                    }
                }
            }

            if (connected_nums.size() == 2) {
                std::vector first_num_line = coordinates[connected_nums[0].first];
                std::vector second_num_line = coordinates[connected_nums[1].first];

                std::pair first_coor = find_coordinate(first_num_line, connected_nums[0].second);
                std::pair second_coor = find_coordinate(second_num_line, connected_nums[1].second);

                int num1 = std::stoi(
                    graph[connected_nums[0].first].substr(first_coor.first,
                    first_coor.second + 1 - first_coor.first)
                );
                int num2 = std::stoi(
                    graph[connected_nums[1].first].substr(second_coor.first,
                    second_coor.second + 1 - second_coor.first)
                );

                total += num1 * num2;
            }
        }
    }

    return total;
}
