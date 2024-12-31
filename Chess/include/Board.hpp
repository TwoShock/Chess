#pragma once
#include <Cell.hpp>
#include <Position.hpp>

#include <functional>
#include <vector>
namespace chess {
constexpr auto BoardSize = 8;
using BoardScanCallback = std::function<void(PieceVariant&,Position)>;
class Board {
 public:
  Board();
  Board(std::vector<std::vector<Cell>> initialState);

  [[nodiscard]] auto getWidth() const -> size_t { return BoardSize; }
  [[nodiscard]] auto getHeight() const -> size_t { return BoardSize; }

  auto setPiece(Position position, std::optional<PieceVariant> piece) -> void;
  auto hasPiece(Position position) const -> bool;
  auto hasPiece(Position position, Color color) const -> bool;
  /*
  This will set the highlighted flag on the cells of the board reachable from
  the piece at position. This flag is consumed when displaying the board. Nice
  for test in dev could come in handy later when adding graphics
  */
  auto highlightMoves(Position position) -> void;
  auto resetHighlightedMoves() -> void;

  auto getCell(Position position) const -> const Cell*;

  template <typename T>
  auto hasPiece(Position position) const -> bool {
    if (!hasPiece(position)) {
      return false;
    }
    const PieceVariant* piece = getCell(position)->getPiece();
    return std::holds_alternative<T>(*piece);
  }

  template <typename T>
  auto hasPiece(Position position, Color color) const -> bool {
    if (!hasPiece(position, color)) {
      return false;
    }
    const PieceVariant* piece = getCell(position)->getPiece();
    return std::holds_alternative<T>(*piece);
  }

  template <class T>
  auto getPiece(Position position) const -> const T* {
    if (!hasPiece<T>(position)) {
      return nullptr;
    }
    const PieceVariant* piece = getCell(position)->getPiece();
    return &std::get<T>(*piece);
  }

  friend std::ostream& operator<<(std::ostream& os, const Board& cell);
  auto isValidCellPosition(Position position) const -> bool;
  auto wouldMoveResultInCheck(Move move) const -> bool;
  auto findKing(Color color) const -> Position;
  auto scanPieces(BoardScanCallback callback) -> void;

 private:
  mutable std::vector<std::vector<Cell>> m_cells;
};
}  // namespace chess
