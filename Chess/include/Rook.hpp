#pragma once
#include "IDisplay.hpp"
#include "Piece.hpp"
#include "utils.hpp"

#include <string>
namespace chess {
class Rook : public Piece, public IDisplay {
 public:
  Rook(Color color) : Piece(color) {}

  auto display() const -> std::string override {
    return pieceDisplayHelper(getColor(), 'r');
  }
};
}  // namespace chess
