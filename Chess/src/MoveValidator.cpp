#include "MoveValidator.hpp"

#include <Board.hpp>
#include <Turn.hpp>
namespace chess {
auto computeMoveStatus(Move move, const Board& board) -> MoveStatus {
  return MoveStatus::Valid;
}
}  // namespace chess
