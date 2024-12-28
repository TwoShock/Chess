#include <Move.hpp>
#include <MovementHelper.hpp>
#include <stdexcept>
#include <unordered_set>
#include <utils.hpp>
#include <vector>

namespace chess {
namespace {
using PositionSet = std::unordered_set<Position, PositionHash>;
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
  if (dynamic_cast<const Queen*>(&piece) == nullptr &&
      dynamic_cast<const Bishop*>(&piece) == nullptr) {
    throw std::runtime_error(
        "Can not get diagonal moves for a piece that isn't a queen or a "
        "bishop.");
  }
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
  if (dynamic_cast<const Rook*>(&piece) == nullptr &&
      dynamic_cast<const Queen*>(&piece) == nullptr) {
    throw std::runtime_error(
        "Can not get vertical and horizontal moves for a piece that isn't a "
        "queen or a "
        "rook.");
  }
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
}  // namespace chess