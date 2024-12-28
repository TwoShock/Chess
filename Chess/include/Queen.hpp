#pragma once
#include "IDisplay.hpp"
#include "Piece.hpp"
#include "utils.hpp"

#include <string>
namespace chess {
class Queen : public Piece, public IDisplay {
 public:
  Queen(Color color) : Piece(color) {}

  auto display() const -> std::string override {
    return pieceDisplayHelper(getColor(), 'q');
  }
  auto getPossibleMoves(Position startPosition,
                        const Board& board) const -> Moves override;
};
}  // namespace chess
