#include "MoveValidator.hpp"

#include <Board.hpp>
#include <Turn.hpp>
namespace chess {
auto filterValidMoves(Moves moves, const Board& board) -> Moves {
  Moves validMoves;
  for (const auto& move : moves) {
    if (!board.wouldMoveResultInCheck(move)) {
      validMoves.insert(move);
    }
  }
  return validMoves;
}
}  // namespace chess
