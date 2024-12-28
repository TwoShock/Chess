#include <Bishop.hpp>
#include <Board.hpp>
#include <DiagonalMoveHelper.hpp>
#include <Move.hpp>
#include <MoveValidator.hpp>

namespace chess {
auto Bishop::getPossibleMoves(Position startPosition,
                              const Board& board) const -> Moves {
  Moves possibleMoves{getDiagonalMoves(*this, startPosition, board)};
  return filterValidMoves(possibleMoves, board);
}

}  // namespace chess