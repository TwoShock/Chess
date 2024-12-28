#include <Bishop.hpp>
#include <Board.hpp>
#include <Move.hpp>
#include <MoveValidator.hpp>
#include <MovementHelper.hpp>

namespace chess {
auto Bishop::getPossibleMoves(Position startPosition,
                              const Board& board) const -> Moves {
  Moves possibleMoves{getDiagonalMoves(*this, startPosition, board)};
  return filterValidMoves(possibleMoves, board);
}

}  // namespace chess