#include <DiagonalMoveHelper.hpp>
#include <Move.hpp>
#include <unordered_set>
#include <utils.hpp>
#include <vector>

namespace chess {
namespace {
using PositionSet = std::unordered_set<Position, PositionHash>;
enum class DiagonalDirection { TopRight, TopLeft, BottomRight, BottomLeft };
auto toDirectionPair(DiagonalDirection direction) -> std::pair<int, int> {
  switch (direction) {
    case DiagonalDirection::TopRight: {
      return {1, 1};
    }
    case DiagonalDirection::TopLeft: {
      return {1, -1};
    }
    case DiagonalDirection::BottomLeft: {
      return {-1, -1};
    }
    case DiagonalDirection::BottomRight: {
      return {-1, 1};
    }
  }
}
auto getAllEndingPositionsForDiagonalDirection(const Piece& piece,
                                               Position startPosition,
                                               const Board& board,
                                               DiagonalDirection direction)
    -> PositionSet {
  Position currentPosition{startPosition};
  PositionSet endingPositionsAlongDiagonalDirection;
  while (currentPosition == startPosition ||
         (board.isValidCellPosition(currentPosition) &&
          !board.hasPiece(currentPosition))) {
    if (currentPosition != startPosition) {
      endingPositionsAlongDiagonalDirection.insert(currentPosition);
    }
    auto [x, y] = currentPosition;
    auto [dx, dy] = toDirectionPair(direction);

    currentPosition = {x + dx, y + dy};
  }//loop invariant is while we are on an empty cell keep moving diagonally
  if (board.isValidCellPosition(currentPosition) &&
      board.hasPiece(currentPosition, piece.getOppositeColor())) {
    endingPositionsAlongDiagonalDirection.insert(currentPosition);
  }
  return endingPositionsAlongDiagonalDirection;
}
}  // namespace
auto getDiagonalMoves(const Piece& piece,
                      Position startPosition,
                      const Board& board) -> Moves {
  PositionSet topRightPositions{getAllEndingPositionsForDiagonalDirection(
      piece, startPosition, board, DiagonalDirection::TopRight)};
  PositionSet topLeftPositions{getAllEndingPositionsForDiagonalDirection(
      piece, startPosition, board, DiagonalDirection::TopLeft)};
  PositionSet bottomLeftPosition{getAllEndingPositionsForDiagonalDirection(
      piece, startPosition, board, DiagonalDirection::BottomLeft)};
  PositionSet bottomRightPosition{getAllEndingPositionsForDiagonalDirection(
      piece, startPosition, board, DiagonalDirection::BottomRight)};
  Moves possibleMoves;
  auto updatePossibleMoves = [&possibleMoves,
                              &startPosition](const PositionSet& positionSet) {
    for (auto endingPosition : positionSet) {
      possibleMoves.insert({startPosition, endingPosition});
    }
  };
  updatePossibleMoves(topRightPositions);
  updatePossibleMoves(topLeftPositions);
  updatePossibleMoves(bottomRightPosition);
  updatePossibleMoves(bottomLeftPosition);
  return possibleMoves;
}
}  // namespace chess