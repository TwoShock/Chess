#include "Rook.hpp"
#include <MoveValidator.hpp>
#include <MovementHelper.hpp>
namespace chess {

auto Rook::getPossibleMoves(Position startPosition,
                            const Board& board) const -> Moves {
  Moves possibleMoves{
      getVerticalAndHorizontalMoves(*this, startPosition, board)};
  return filterValidMoves(possibleMoves, board);
}
}  // namespace chess