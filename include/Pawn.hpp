#pragma once

#include <Position.hpp>
#include "IDisplay.hpp"
#include "Piece.hpp"
#include "utils.hpp"

#include <string>

namespace chess {
class Pawn : public Piece, public IDisplay {
 public:
  Pawn(Color color)
      : Piece(color), m_firstMove(true), m_canBeTakenByEnpassant(false) {}
  auto display() const -> std::string override {
    return pieceDisplayHelper(getColor(), 'p');
  }

  auto getPossibleMoves(Position startPosition,
                        const Board& board) const -> Moves override;
  [[nodiscard]] auto canBeTakenByEnpassant() const -> bool {
    return m_canBeTakenByEnpassant;
  }
  auto setCanBeTakenByEnpassant(bool canBeTaken) -> void {
    m_canBeTakenByEnpassant = canBeTaken;
  }

  [[nodiscard]] auto isFirstMove() const { return m_firstMove; }
  auto setIsFirstMove(bool isFirstMove) -> void { m_firstMove = isFirstMove; }

 private:
  [[nodiscard]] auto getForwardMoves(Position startPosition,
                                     const Board& board) const -> Moves;
  [[nodiscard]] auto getCaptureMoves(Position startPosition,
                                     const Board& board) const -> Moves;
  [[nodiscard]] auto getEnpassantCaptureMoves(Position startPosition,
                                              const Board& board) const
      -> Moves;
  [[nodiscard]] auto getForwardDirection() const -> int;
  struct MoveSet {
    Move m_forwardOnce;
    Move m_forwardTwice;
    Move m_leftDiagonal;
    Move m_rightDiagonal;
  };
  struct PositionsOfInterest {
    Position m_cellInFront;
    Position m_twoCellsInFront;
    Position m_leftDiagonal;
    Position m_rightDiagonal;
    Position m_leftOfStart;
    Position m_rightOfStart;
  };
  [[nodiscard]] auto getMoveSet(Position startPosition) const -> MoveSet;
  [[nodiscard]] auto getPositionsOfInterest(Position startPosition) const
      -> PositionsOfInterest;
  bool m_firstMove;
  bool m_canBeTakenByEnpassant;
};
}  // namespace chess