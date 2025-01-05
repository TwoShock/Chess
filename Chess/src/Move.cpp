#include <Move.hpp>
#include <Position.hpp>
namespace chess {
auto mergeMoveSets(std::initializer_list<Moves> moves) -> Moves {
  Moves result;
  for (const auto& set : moves) {
    result.insert(set.begin(), set.end());
  }
  return result;
}
auto reverseMove(Move move) -> Move {
  auto [start, end] = move;
  return {end, start};
}

namespace {
auto fromChessCoordinate(const std::string& coordinate) -> Position {
  auto rowIt = std::find(rowNumbers.begin(), rowNumbers.end(), coordinate[1]);
  auto colIt = std::find(columnLetters.begin(), columnLetters.end(), coordinate[0]);
  return {std::distance(rowNumbers.begin(), rowIt), std::distance(columnLetters.begin(),colIt)};
}
}  // namespace
auto toMove(const std::string& move) -> Move {
  const std::string from = move.substr(0, 2);
  const std::string to = move.substr(3, 2);

  return {fromChessCoordinate(from), fromChessCoordinate(to)};
}
}  // namespace chess