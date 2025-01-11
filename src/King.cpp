#include "King.hpp"
#include <MoveValidator.hpp>
#include <MovementHelper.hpp>
#include <optional>
namespace chess {

auto King::getPossibleMoves(Position startPosition, const Board& board) const
    -> Moves {
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
    if (!board.isValidCellPosition(position)) {
      continue;
    }
    if (!board.hasPiece(position) ||
        board.hasPiece(position, getOppositeColor())) {
      possibleMoves.insert({startPosition, position});
    }
  }
  std::vector<CastlingMove> castlingMoves =
      getCastlingMoves(startPosition, board);
  for (const auto& castlingMove : castlingMoves) {
    auto [kingsMove, _] = castlingMove;
    possibleMoves.insert(kingsMove);
  }
  return filterValidMoves(possibleMoves, board);
}
auto King::getCastlingMoves(Position startPosition, const Board& board) const
    -> std::vector<CastlingMove> {
  if (hasMoved() || hasCastled()) {
    return {};
  }
  std::vector<CastlingMove> castlingMoves;
  std::optional<CastlingMove> rightCastlingMove{
      getRightCastlingMove(startPosition, board)};
  std::optional<CastlingMove> leftCastlingMove{
      getLeftCastlingMove(startPosition, board)};
  if (rightCastlingMove.has_value()) {
    castlingMoves.push_back(rightCastlingMove.value());
  }

  if (leftCastlingMove.has_value()) {
    castlingMoves.push_back(leftCastlingMove.value());
  }
  return castlingMoves;
}
namespace {
auto existsPiecesBetweenKingAndRook(Position kingPosition,
                                    Position rookPosition,
                                    const Board& board) {
  const auto [x, y] = kingPosition;
  const auto [_, yRook] = rookPosition;
  const int distance = std::abs(y - yRook);
  for (int yPos = y + 1; yPos < y + distance; yPos++) {
    if (board.hasPiece({x, yPos})) {
      return true;
    }
  }
  return false;
}
}  // namespace
auto King::getRightCastlingMove(Position startPosition,
                                const Board& board) const
    -> std::optional<CastlingMove> {
  const auto [x, y] = startPosition;
  const int startingRow = getStartingRow();
  const Position rightRookPosition{startingRow, y + 3};

  if (!board.hasPiece<Rook>(rightRookPosition, getColor()) ||
      existsPiecesBetweenKingAndRook(startPosition, rightRookPosition, board)) {
    return std::nullopt;
  }
  if (board.getPiece<Rook>(rightRookPosition)->hasMoved()) {
    return std::nullopt;
  }
  const Position oneTileRight{x, y + 1};
  const Position twoTileRight{x, y + 2};
  bool kingInCheckOrPassesThroughOrFinishesOnATileThatWouldPutHimInCheck =
      board.wouldMoveResultInCheck({startPosition, oneTileRight}) ||
      board.wouldMoveResultInCheck({startPosition, twoTileRight}) ||
      board.wouldMoveResultInCheck({startPosition, startPosition});
  if (kingInCheckOrPassesThroughOrFinishesOnATileThatWouldPutHimInCheck) {
    return std::nullopt;
  }
  return std::make_pair<Move, Move>({startPosition, twoTileRight},
                                    Move{rightRookPosition, oneTileRight});
}

auto King::getLeftCastlingMove(Position startPosition, const Board& board) const
    -> std::optional<CastlingMove> {
  const auto [x, y] = startPosition;
  const int startingRow = getStartingRow();
  const Position leftRookPosition{startingRow, y - 4};

  if (!board.hasPiece<Rook>(leftRookPosition, getColor()) ||
      existsPiecesBetweenKingAndRook(leftRookPosition, startPosition, board)) {
    return std::nullopt;
  }
  if (board.getPiece<Rook>(leftRookPosition)->hasMoved()) {
    return std::nullopt;
  }
  const Position oneTileLeft{x, y - 1};
  const Position twoTileLeft{x, y - 2};
  const Position threeTileLeft{x, y - 3};

  bool kingInCheckOrPassesThroughOrFinishesOnATileThatWouldPutHimInCheck =
      board.wouldMoveResultInCheck({startPosition, oneTileLeft}) ||
      board.wouldMoveResultInCheck({startPosition, twoTileLeft}) ||
      board.wouldMoveResultInCheck({startPosition, threeTileLeft}) ||
      board.wouldMoveResultInCheck({startPosition, startPosition});
  if (kingInCheckOrPassesThroughOrFinishesOnATileThatWouldPutHimInCheck) {
    return std::nullopt;
  }
  return std::make_pair<Move, Move>({startPosition, twoTileLeft},
                                    Move{leftRookPosition, oneTileLeft});
}

auto King::getStartingRow() const -> int {
  switch (getColor()) {
    case Color::White: {
      return 7;
    }
    case Color::Black: {
      return 0;
    }
  }
  return 0;
}

}  // namespace chess