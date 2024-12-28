#pragma once
#include <Bishop.hpp>
#include <King.hpp>
#include <Knight.hpp>
#include <Pawn.hpp>
#include <Queen.hpp>
#include <Rook.hpp>
#include <optional>
#include <variant>

#include "Piece.hpp"
namespace chess {
using PieceVariant = std::variant<King, Queen, Rook, Bishop, Knight, Pawn>;
class Cell : public IDisplay {
 public:
  Cell();
  Cell(PieceVariant piece);
  [[nodiscard]] auto hasPiece() const -> bool { return m_piece.has_value(); }
  [[nodiscard]] auto getPiece() const -> const PieceVariant* {
    if (hasPiece()) {
      return &m_piece.value();
    }
    return nullptr;
  }
  [[nodiscard]] auto getPieceColor() const -> std::optional<Color> {
    if (hasPiece()) {
      return std::visit([](const auto& piece) { return piece.getColor(); },
                        m_piece.value());
    }
    return std::nullopt;
  }
  auto setPiece(std::optional<PieceVariant> piece) -> void {
    if (!piece.has_value()) {
      m_piece.reset();
    }
    m_piece = piece;
  }

  [[nodiscard]] auto display() const -> std::string override;
  friend std::ostream& operator<<(std::ostream& os, const Cell& cell);

 private:
  std::optional<PieceVariant> m_piece;
};
}  // namespace chess
