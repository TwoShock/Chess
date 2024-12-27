#include "Piece.hpp"

#include "Board.hpp"
namespace chess {
auto Piece::getOppositeColor() const -> Color {
  switch (m_color) {
    case Color::White: {
      return Color::Black;
    }
    case Color::Black: {
      return Color::White;
    }
  }
}
auto Piece::getPossibleMoves(Position startPosition,
                             const Board& board) const -> Moves {
  return {};
}

auto Piece::isFriendly(const Piece& other) const -> bool {
  return other.getColor() == getColor();
}

auto Piece::isEnemy(const Piece& other) const -> bool {
  return other.getColor() != getColor();
}
}  // namespace chess
