#include "Knight.hpp"
#include <Board.hpp>
#include <Move.hpp>
#include <MoveValidator.hpp>
namespace chess {
auto Knight::getPossibleMoves(Position startPosition,
                              const Board& board) const -> Moves {
  Moves possibleMoves;
  auto [x, y] = startPosition;
  Position topRight{x + 2, y + 1};
  Position topLeft{x + 2, y - 1};
  Position bottomRight{x - 2, y + 1};
  Position bottomLeft{x - 2, y - 1};
  auto updatePossibleMoves = [this, &board, &possibleMoves,
                              &startPosition](Position position) {
    bool isCellUnoccupied =
        !board.hasPiece(position) && board.isValidCellPosition(position);
    bool isCellOcuupiedWithEnemyPiece =
        board.hasPiece(position, getOppositeColor());
    if (isCellUnoccupied || isCellOcuupiedWithEnemyPiece) {
      possibleMoves.insert({startPosition, position});
    }
  };
  updatePossibleMoves(topRight);
  updatePossibleMoves(topLeft);
  updatePossibleMoves(bottomRight);
  updatePossibleMoves(bottomLeft);

  return filterValidMoves(possibleMoves, board);
}
}  // namespace chess