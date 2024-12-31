#include <Position.hpp>
#include <array>
#include <format>
namespace chess {

auto mergePositionSets(const std::vector<PositionSet>& postionSets)
    -> PositionSet {
  PositionSet mergedPositionSet;
  for (const auto& positionSet : postionSets) {
    mergedPositionSet.insert(positionSet.begin(), positionSet.end());
  }
  return mergedPositionSet;
}
namespace {
static std::array<char, 8> columnLetters = {'a', 'b', 'c', 'd',
                                            'e', 'f', 'g', 'h'};
static std::array<char, 8> rowNumbers = {'8', '7', '6', '5',
                                         '4', '3', '2', '1'};
}  // namespace
auto toChessCoordinates(Position position) -> std::string {
  auto [x, y] = position;
  return std::format("{}{}", columnLetters[y], columnLetters[x]);
}

auto toString(Position position) -> std::string {
  return toChessCoordinates(position);
}
}  // namespace chess