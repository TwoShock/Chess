#pragma once

#include <Move.hpp>
#include <string>
#include "IDisplay.hpp"
#include "Piece.hpp"
#include "utils.hpp"

namespace chess {
class Knight : public Piece, public IDisplay {
 public:
  Knight(Color color) : Piece(color) {}
  auto display() const -> std::string override {
    return pieceDisplayHelper(getColor(), 'n');
  }
  auto getPossibleMoves(Position startPosition,
                        const Board& board) const -> Moves override;
};
}  // namespace chess
