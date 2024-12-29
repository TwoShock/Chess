#include <Position.hpp>
namespace chess {

auto mergePositionSets(const std::vector<PositionSet>& postionSets)
    -> PositionSet {
  PositionSet mergedPositionSet;
  for (const auto& positionSet : postionSets) {
    mergedPositionSet.insert(positionSet.begin(), positionSet.end());
  }
  return mergedPositionSet;
}
}  // namespace chess