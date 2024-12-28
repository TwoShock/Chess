#include "King.hpp"
#include <MoveValidator.hpp>
#include <MovementHelper.hpp>
namespace chess {

auto King::getPossibleMoves(Position startPosition,
                            const Board& board) const -> Moves {
  const auto [x, y] = startPosition;
  const Position forward{x + 1, y};
  const Position backward{x - 1, y};
  const Position left{x, y - 1};
  const Position right{x, y + 1};
  const Position topLeft{x + 1, y - 1};
  const Position topRight{x + 1, y + 1};
  const Position bottomLeft{x - 1, y - 1};
  const Position bottomRight{x - 1, y + 1};
  const std::vector<Position> possibleEndingPositions{
      forward, backward, left,       right,
      topLeft, topRight, bottomLeft, bottomRight};
  Moves possibleMoves;
  for (const auto& position : possibleEndingPositions) {
    if (!board.hasPiece(position) ||
        board.hasPiece(position, getOppositeColor())) {
      possibleMoves.insert({startPosition, position});
    }
  }
  return filterValidMoves(possibleMoves, board);
}
}  // namespace chess