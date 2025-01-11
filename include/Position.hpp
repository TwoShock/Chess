#pragma once
#include <array>
#include <string>
#include <unordered_set>
#include <utility>
namespace chess {
inline std::array<char, 8> columnLetters = {'a', 'b', 'c', 'd',
                                            'e', 'f', 'g', 'h'};
inline std::array<char, 8> rowNumbers = {'8', '7', '6', '5',
                                         '4', '3', '2', '1'};
using Position = std::pair<int, int>;
struct PositionHash {
  std::size_t operator()(const std::pair<int, int>& p) const {
    return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
  }
};
using PositionSet = std::unordered_set<Position, PositionHash>;
[[nodiscard]] auto mergePositionSets(
    const std::vector<PositionSet>& postionSets) -> PositionSet;
[[nodiscard]] auto toChessCoordinates(Position position) -> std::string;
[[nodiscard]] auto toString(Position position) -> std::string;
static Position NotFound{-1, -1};
}  // namespace chess
