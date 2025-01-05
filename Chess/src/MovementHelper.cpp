#include <Move.hpp>
#include <MovementHelper.hpp>
#include <Position.hpp>
#include <stdexcept>
#include <unordered_set>
#include <utils.hpp>
#include <vector>

namespace chess {
namespace {
enum class Direction {
  TopRightDiagonal,
  TopLeftDiagonal,
  BottomRightDiagonal,
  BottomLeftDiagonal,
  Left,
  Right,
  Forward,
  Backward
};
auto toDirectionPair(Direction direction) -> std::pair<int, int> {
  switch (direction) {
    case Direction::TopRightDiagonal: {
      return {1, 1};
    }
    case Direction::TopLeftDiagonal: {
      return {1, -1};
    }
    case Direction::BottomLeftDiagonal: {
      return {-1, -1};
    }
    case Direction::BottomRightDiagonal: {
      return {-1, 1};
    }
    case Direction::Left: {
      return {0, -1};
    }
    case Direction::Right: {
      return {0, 1};
    }
    case Direction::Forward: {
      return {1, 0};
    }
    case Direction::Backward: {
      return {-1, 0};
    }
  }
}
auto getAllEndingPositionsForDirection(const Piece& piece,
                                       Position startPosition,
                                       const Board& board,
                                       Direction direction) -> PositionSet {
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
  }  // loop invariant is while we are on an empty cell keep moving
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
  PositionSet topRightPositions{getAllEndingPositionsForDirection(
      piece, startPosition, board, Direction::TopRightDiagonal)};
  PositionSet topLeftPositions{getAllEndingPositionsForDirection(
      piece, startPosition, board, Direction::TopLeftDiagonal)};
  PositionSet bottomLeftPosition{getAllEndingPositionsForDirection(
      piece, startPosition, board, Direction::BottomLeftDiagonal)};
  PositionSet bottomRightPosition{getAllEndingPositionsForDirection(
      piece, startPosition, board, Direction::BottomRightDiagonal)};
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
auto getVerticalAndHorizontalMoves(const Piece& piece,
                                   Position startPosition,
                                   const Board& board) -> Moves {
  PositionSet leftPositions{getAllEndingPositionsForDirection(
      piece, startPosition, board, Direction::Left)};
  PositionSet rightPositions{getAllEndingPositionsForDirection(
      piece, startPosition, board, Direction::Right)};
  PositionSet forwardPositions{getAllEndingPositionsForDirection(
      piece, startPosition, board, Direction::Forward)};
  PositionSet backwardPositions{getAllEndingPositionsForDirection(
      piece, startPosition, board, Direction::Backward)};
  Moves possibleMoves;
  auto updatePossibleMoves = [&possibleMoves,
                              &startPosition](const PositionSet& positionSet) {
    for (auto endingPosition : positionSet) {
      possibleMoves.insert({startPosition, endingPosition});
    }
  };
  updatePossibleMoves(leftPositions);
  updatePossibleMoves(rightPositions);
  updatePossibleMoves(forwardPositions);
  updatePossibleMoves(backwardPositions);
  return possibleMoves;
}
auto getKnightTypeMoves(const Piece& piece,
                        Position startPosition,
                        const Board& board) -> Moves {
  Moves possibleMoves;
  auto [x, y] = startPosition;
  const Position upRight{x + 2, y + 1};
  const Position upLeft{x + 2, y - 1};
  const Position downRight{x - 2, y + 1};
  const Position downLeft{x - 2, y - 1};
  const Position rightUp{x + 1, y + 2};
  const Position leftUp{x + 1, y - 2};

  auto updatePossibleMoves = [&piece, &board, &possibleMoves,
                              &startPosition](Position position) {
    bool isCellUnoccupied =
        !board.hasPiece(position) && board.isValidCellPosition(position);
    bool isCellOcuupiedWithEnemyPiece =
        board.hasPiece(position, piece.getOppositeColor());
    if (isCellUnoccupied || isCellOcuupiedWithEnemyPiece) {
      possibleMoves.insert({startPosition, position});
    }
  };
  updatePossibleMoves(upRight);
  updatePossibleMoves(upLeft);
  updatePossibleMoves(downRight);
  updatePossibleMoves(downLeft);
  updatePossibleMoves(rightUp);
  updatePossibleMoves(leftUp);

  return possibleMoves;
}
}  // namespace chess