#include <Position.hpp>
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
auto toChessCoordinates(Position position) -> std::string {
  auto [x, y] = position;
  return std::format("{}{}", columnLetters[y], rowNumbers[x]);
}

auto toString(Position position) -> std::string {
  return toChessCoordinates(position);
}
}  // namespace chess