#include "Pawn.hpp"

#include <Board.hpp>
#include <Move.hpp>
#include <MoveValidator.hpp>

namespace chess {

auto Pawn::getPossibleMoves(Position startPosition,
                            const Board& board) const -> Moves {
  Moves forwardMoves{getForwardMoves(startPosition, board)};
  Moves captureMoves{getCaptureMoves(startPosition, board)};
  Moves allMoves{mergeMoveSets({forwardMoves, captureMoves})};
  return filterValidMoves(allMoves, board);
}
auto Pawn::getForwardMoves(Position startPosition,
                           const Board& board) const -> Moves {
  Moves moves;
  PositionsOfInterest positionsOfInterest{
      getPositionsOfInterest(startPosition)};
  MoveSet possibleMoves{getMoveSet(startPosition)};
  if (m_firstMove && !board.hasPiece(positionsOfInterest.m_cellInFront) &&
      !board.hasPiece(positionsOfInterest.m_twoCellsInFront) &&
      board.isValidCellPosition(positionsOfInterest.m_twoCellsInFront)) {
    moves.insert(possibleMoves.m_forwardTwice);
  }
  if (board.isValidCellPosition(positionsOfInterest.m_cellInFront) &&
      !board.hasPiece(positionsOfInterest.m_cellInFront)) {
    moves.insert(possibleMoves.m_forwardOnce);
  }
  return moves;
}
auto Pawn::getCaptureMoves(Position startPosition,
                           const Board& board) const -> Moves {
  Moves moves;
  PositionsOfInterest positionsOfInterest{
      getPositionsOfInterest(startPosition)};
  MoveSet possibleMoves{getMoveSet(startPosition)};
  Color opponentColor = getOppositeColor();
  if (board.isValidCellPosition(positionsOfInterest.m_rightDiagonal) &&
      board.hasPiece(positionsOfInterest.m_rightDiagonal, opponentColor)) {
    moves.insert(possibleMoves.m_rightDiagonal);
  }
  if (board.isValidCellPosition(positionsOfInterest.m_leftDiagonal) &&
      board.hasPiece(positionsOfInterest.m_leftDiagonal, opponentColor)) {
    moves.insert(possibleMoves.m_leftDiagonal);
  }
  return mergeMoveSets({getEnpassantCaptureMoves(startPosition, board), moves});
}
auto Pawn::getEnpassantCaptureMoves(Position startPosition,
                                    const Board& board) const -> Moves {
  Color opponentColor = getOppositeColor();
  Moves moves;
  PositionsOfInterest positionsOfInterest{
      getPositionsOfInterest(startPosition)};
  MoveSet possibleMoves{getMoveSet(startPosition)};
  auto canPieceBeTakenByEnpassant = [&board,
                                     opponentColor](Position piecePosition) {
    if (board.hasPiece<Pawn>(piecePosition, opponentColor)) {
      const Pawn* opponentPawn = board.getPiece<Pawn>(piecePosition);
      return opponentPawn->canBeTakenByEnpassant();
    }
    return false;
  };
  if (canPieceBeTakenByEnpassant(positionsOfInterest.m_leftOfStart)) {
    moves.insert(possibleMoves.m_leftDiagonal);
  }
  if (canPieceBeTakenByEnpassant(positionsOfInterest.m_rightOfStart)) {
    moves.insert(possibleMoves.m_rightDiagonal);
  }
  return moves;
}
auto Pawn::getForwardDirection() const -> int {
  switch (getColor()) {
    case Color::White: {
      return -1;
    }
    case Color::Black: {
      return 1;
    }
  }
  return 1;
}

auto Pawn::getPositionsOfInterest(Position startPosition) const
    -> PositionsOfInterest {
  auto [x, y] = startPosition;
  Position cellInFront{x + getForwardDirection(), y};
  Position twoCellsInFront{x + 2 * getForwardDirection(), y};
  Position leftDiagonal{x + getForwardDirection(), y - 1};
  Position rightDiagonal{x + getForwardDirection(), y + 1};
  Position leftOfStart{x, y - 1};
  Position rightOfStart{x, y + 1};
  return {cellInFront,   twoCellsInFront, leftDiagonal,
          rightDiagonal, leftOfStart,     rightOfStart};
}
auto Pawn::getMoveSet(Position startPosition) const -> MoveSet {
  PositionsOfInterest positionsOfInterest{
      getPositionsOfInterest(startPosition)};
  Move m_forwardOnce{startPosition, positionsOfInterest.m_cellInFront};
  Move m_forwardTwice{startPosition, positionsOfInterest.m_twoCellsInFront};
  Move m_leftDiagonal{startPosition, positionsOfInterest.m_leftDiagonal};
  Move m_rightDiagonal{startPosition, positionsOfInterest.m_rightDiagonal};
  return {m_forwardOnce, m_forwardTwice, m_leftDiagonal, m_rightDiagonal};
}
}  // namespace chess
