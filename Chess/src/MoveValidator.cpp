#include "MoveValidator.hpp"

#include <Board.hpp>
#include <Turn.hpp>
namespace chess {
auto computeMoveStatus(Move move, const Board& board) -> MoveStatus {
  return MoveStatus::Valid;
}
auto filterValidMoves(Moves moves, const Board& board) -> Moves {
  Moves validMoves;
  for (const auto& move : moves) {
    if (computeMoveStatus(move, board) == MoveStatus::Valid) {
      validMoves.insert(move);
    }
  }
  return validMoves;
}
}  // namespace chess
