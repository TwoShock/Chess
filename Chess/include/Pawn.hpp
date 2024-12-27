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

 private:
  [[nodiscard]] auto getForwardMoves(Position startPosition,
                                     const Board& board) const -> Moves;
  [[nodiscard]] auto getCaptureMoves(Position startPosition,
                                     const Board& board) const -> Moves;
  [[nodiscard]] auto getEnpassantCaptureMoves(Position startPosition,
                                              const Board& board) const
      -> Moves;
  bool m_firstMove;
  bool m_canBeTakenByEnpassant;
};
}  // namespace chess
