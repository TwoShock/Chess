#include <Move.hpp>
namespace chess {
auto mergeMoveSets(std::initializer_list<Moves> moves) -> Moves {
  Moves result;
  for (const auto& set : moves) {
    result.insert(set.begin(), set.end());
  }
  return result;
}
}  // namespace chess