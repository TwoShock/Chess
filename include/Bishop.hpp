#pragma once

#include <Move.hpp>
#include "IDisplay.hpp"
#include "Piece.hpp"
#include "utils.hpp"

#include <string>

namespace chess {
class Bishop : public Piece, public IDisplay {
 public:
  Bishop(Color color) : Piece(color) {}
  auto display() const -> std::string override {
    return pieceDisplayHelper(getColor(), 'b');
  }
  auto getPossibleMoves(Position startPosition,
                        const Board& board) const -> Moves override;
};
}  // namespace chess
