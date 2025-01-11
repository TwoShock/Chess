#include "Queen.hpp"
#include <MoveValidator.hpp>
#include <MovementHelper.hpp>
namespace chess {

auto Queen::getPossibleMoves(Position startPosition,
                             const Board& board) const -> Moves {
  Moves verticalAndHorizontalMoves{
      getVerticalAndHorizontalMoves(*this, startPosition, board)};
  Moves diagonalMoves{getDiagonalMoves(*this, startPosition, board)};
  Moves possibleMoves{
      mergeMoveSets({verticalAndHorizontalMoves, diagonalMoves})};
  return filterValidMoves(possibleMoves, board);
}
}  // namespace chess