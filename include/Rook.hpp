#pragma once
#include <Move.hpp>
#include "IDisplay.hpp"
#include "Piece.hpp"
#include "utils.hpp"

#include <string>
namespace chess {
class Rook : public Piece, public IDisplay {
 public:
  Rook(Color color) : Piece(color), m_hasMoved(false) {}

  auto display() const -> std::string override {
    return pieceDisplayHelper(getColor(), 'r');
  }
  auto getPossibleMoves(Position startPosition,
                        const Board& board) const -> Moves override;
  [[nodiscard]] auto hasMoved() const -> bool { return m_hasMoved; }
  auto setHasMoved(bool hasMoved) -> void { m_hasMoved = hasMoved; }

 private:
  bool m_hasMoved;
};
}  // namespace chess
