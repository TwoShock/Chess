#include "Knight.hpp"
#include <Board.hpp>
#include <Move.hpp>
#include <MoveValidator.hpp>
#include <MovementHelper.hpp>
namespace chess {
auto Knight::getPossibleMoves(Position startPosition,
                              const Board& board) const -> Moves {
  Moves possibleMoves{getKnightTypeMoves(*this, startPosition, board)};
  return filterValidMoves(possibleMoves, board);
}
}  // namespace chess