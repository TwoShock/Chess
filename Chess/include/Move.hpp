#pragma once
#include <Position.hpp>
#include <unordered_set>
#include <utility>
namespace chess {
using Move = std::pair<Position, Position>;
struct MoveHash {
  std::size_t operator()(const Move& move) const {
    PositionHash hash;
    size_t firstHash = hash(move.first);
    size_t secondHash = hash(move.second);
    return firstHash ^ (secondHash << 1);
  }
};
struct MoveEq {
  std::size_t operator()(const Move& lhs, const Move& rhs) const {
    return lhs.first == rhs.first && lhs.second == rhs.second;
  }
};
using Moves = std::unordered_set<Move, MoveHash, MoveEq>;
auto mergeMoveSets(std::initializer_list<Moves> moves) -> Moves;

}  // namespace chess
