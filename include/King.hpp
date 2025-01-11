#pragma once
#include "IDisplay.hpp"
#include "Piece.hpp"
#include "utils.hpp"

#include <optional>
#include <string>
namespace chess {
using CastlingMove = std::pair<Move, Move>;
class King : public Piece, public IDisplay {
 public:
  King(Color color) : Piece(color), m_hasMoved(false), m_hasCastled(false) {}

  auto display() const -> std::string override {
    return pieceDisplayHelper(getColor(), 'k');
  }

  auto getPossibleMoves(Position startPosition,
                        const Board& board) const -> Moves override;
  [[nodiscard]] auto hasMoved() const -> bool { return m_hasMoved; }
  auto setHasMoved(bool hasMoved) -> void { m_hasMoved = hasMoved; }

  [[nodiscard]] auto hasCastled() const -> bool { return m_hasCastled; }
  auto setHasCastled(bool hasCastled) -> void { m_hasCastled = hasCastled; }
  [[nodiscard]] auto getCastlingMoves(Position startPosition,
                                      const Board& board) const
      -> std::vector<CastlingMove>;

 private:
  [[nodiscard]] auto getRightCastlingMove(Position startPosition,
                                          const Board& board) const
      -> std::optional<CastlingMove>;
  [[nodiscard]] auto getLeftCastlingMove(Position startPosition,
                                         const Board& board) const
      -> std::optional<CastlingMove>;
  [[nodiscard]] auto getStartingRow() const -> int;
  bool m_hasCastled;
  bool m_hasMoved;
};
}  // namespace chess
