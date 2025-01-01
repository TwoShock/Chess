#include <Board.hpp>

#include <Cell.hpp>
#include <King.hpp>
#include <MoveValidator.hpp>
#include <MovementHelper.hpp>
#include <Pawn.hpp>
#include <Piece.hpp>

#include <format>
#include <ostream>
namespace chess {
Board::Board() {
  m_cells = {
      // clang-format off
		{Cell(Rook(Color::Black)),Cell(Knight(Color::Black)),Cell(Bishop(Color::Black)),Cell(Queen(Color::Black)),Cell(King(Color::Black)),Cell(Bishop(Color::Black)),Cell(Knight(Color::Black)),Cell(Rook(Color::Black))},
		{Cell(Pawn(Color::Black)),Cell(Pawn(Color::Black)),Cell(Pawn(Color::Black)),Cell(Pawn(Color::Black)),Cell(Pawn(Color::Black)),Cell(Pawn(Color::Black)),Cell(Pawn(Color::Black)),Cell(Pawn(Color::Black))},
		{Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
		{Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
		{Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
		{Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
		{Cell(Pawn(Color::White)),Cell(Pawn(Color::White)),Cell(Pawn(Color::White)),Cell(Pawn(Color::White)),Cell(Pawn(Color::White)),Cell(Pawn(Color::White)),Cell(Pawn(Color::White)),Cell(Pawn(Color::White))},
		{Cell(Rook(Color::White)),Cell(Knight(Color::White)),Cell(Bishop(Color::White)),Cell(Queen(Color::White)),Cell(King(Color::White)),Cell(Bishop(Color::White)),Cell(Knight(Color::White)),Cell(Rook(Color::White))}
      // clang-format on
  };
}
Board::Board(std::vector<std::vector<Cell>> initialState)
    : m_cells(std::move(initialState)) {}
auto Board::setPiece(Position position,
                     std::optional<PieceVariant> piece) -> void {
  if (isValidCellPosition(position)) {
    auto [x, y] = position;
    if (piece.has_value()) {
      m_cells[x][y].setPiece(piece);
    } else {
      m_cells[x][y] = Cell();
    }
  }
}
auto Board::highlightMoves(Position startPosition) -> void {
  resetHighlightedMoves();
  if (!hasPiece(startPosition)) {
    return;
  }
  const PieceVariant* piece = getCell(startPosition)->getPiece();
  Moves possibleMoves;
  std::visit(
      [&possibleMoves, this, startPosition](const auto& piece) {
        possibleMoves = piece.getPossibleMoves(startPosition, *this);
      },
      *piece);
  Moves moves{filterValidMoves(possibleMoves, *this)};
  for (const auto move : moves) {
    const auto [_, endPosition] = move;
    const auto [x, y] = endPosition;
    m_cells[x][y].setHighlighted(true);
  }
}
auto Board::resetHighlightedMoves() -> void {
  for (auto& row : m_cells) {
    for (auto& cell : row) {
      cell.setHighlighted(false);
    }
  }
}
auto Board::getCell(Position position) const -> const Cell* {
  auto [x, y] = position;
  if (!isValidCellPosition(position)) {
    return nullptr;
  }
  return &m_cells[x][y];
}

auto Board::hasPiece(Position position) const -> bool {
  const Cell* cell = getCell(position);
  if (cell == nullptr) {
    return false;
  }
  return cell->hasPiece();
}
auto Board::hasPiece(Position position, Color color) const -> bool {
  if (!hasPiece(position)) {
    return false;
  }
  const PieceVariant* piece = getCell(position)->getPiece();
  bool isSameColor = false;
  std::visit(
      [&isSameColor, color](const auto& pieceValue) {
        isSameColor = pieceValue.getColor() == color;
      },
      *piece);
  return isSameColor;
}
auto Board::isValidCellPosition(Position position) const -> bool {
  auto [x, y] = position;
  if (x >= 0 && x < getWidth() && y >= 0 && y < getHeight()) {
    return true;
  }
  return false;
}

namespace {
auto currentPlayer(Move move, const Board& board) -> Color {
  auto [startPosition, _] = move;
  if (board.hasPiece(startPosition, Color::White)) {
    return Color::White;
  }
  return Color::Black;
}
auto getEndingPositionsThatHaveEnemyPieces(const Moves& moves,
                                           const Board& board,
                                           Color enemyColor) -> PositionSet {
  PositionSet endingPositionWithEnemyPieces;
  for (const Move& move : moves) {
    const auto [_, endPosition] = move;
    if (board.hasPiece(endPosition, enemyColor)) {
      endingPositionWithEnemyPieces.insert(endPosition);
    }
  }
  return endingPositionWithEnemyPieces;
}
namespace {
struct PotentialChecks {
  PositionSet m_diagonalChecks;
  PositionSet m_horizontalOrVerticalChecks;
  PositionSet m_knightTypeChecks;
};
}  // namespace
auto getPotentialCheckPositions(const Board& board,
                                Color player) -> PotentialChecks {
  Position kingPosition{board.findKing(player)};
  const King* king = board.getPiece<King>(kingPosition);
  const Moves diagonalMovesFromKingsPerspective =
      getDiagonalMoves(*king, kingPosition, board);
  const Moves horizontalAndVerticalMovesFromKingsPerspective =
      getVerticalAndHorizontalMoves(*king, kingPosition, board);
  const Moves knightTypeMovesFromKingsPerspective =
      getKnightTypeMoves(*king, kingPosition, board);

  const PositionSet diagonalEnemies{getEndingPositionsThatHaveEnemyPieces(
      diagonalMovesFromKingsPerspective, board, king->getOppositeColor())};
  const PositionSet horizontalOrVerticalEnemies{
      getEndingPositionsThatHaveEnemyPieces(
          horizontalAndVerticalMovesFromKingsPerspective, board,
          king->getOppositeColor())};
  const PositionSet knightEnemies{getEndingPositionsThatHaveEnemyPieces(
      knightTypeMovesFromKingsPerspective, board, king->getOppositeColor())};
  return {diagonalEnemies, horizontalOrVerticalEnemies, knightEnemies};
}

auto canBeCheckedByBishopOrQueen(const PositionSet& diagonlPositions,
                                 const Board& board,
                                 Color enemy) -> bool {
  for (const auto& position : diagonlPositions) {
    if (board.hasPiece<Bishop>(position, enemy) ||
        board.hasPiece<Queen>(position, enemy)) {
      return true;
    }
  }
  return false;
}

auto canBeCheckedByRookOrQueen(const PositionSet& horizotnalOrVerticalPosition,
                               const Board& board,
                               Color enemy) -> bool {
  for (const auto& position : horizotnalOrVerticalPosition) {
    if (board.hasPiece<Rook>(position, enemy) ||
        board.hasPiece<Queen>(position, enemy)) {
      return true;
    }
  }
  return false;
}

auto canBeCheckedByKnight(const PositionSet& knightPositions,
                          const Board& board,
                          Color enemy) -> bool {
  for (const auto& position : knightPositions) {
    if (board.hasPiece<Knight>(position, enemy)) {
      return true;
    }
  }
  return false;
}
auto canBeCheckedByPawn(const Board& board,
                        const Position kingPosition,
                        Color player,
                        Color enemy) -> bool {
  auto [x, y] = kingPosition;
  const int pawnHorizontalDirection = player == Color::White ? -1 : 1;
  const Position leftDiagonal{x + pawnHorizontalDirection, y - 1};
  const Position rightDiagonal{x + pawnHorizontalDirection, y + 1};

  if (board.hasPiece<Pawn>(leftDiagonal, enemy) ||
      board.hasPiece<Pawn>(rightDiagonal, enemy)) {
    return true;
  }
  return false;
}
}  // namespace

auto Board::wouldMoveResultInCheck(Move move) const -> bool {
  const Color player{currentPlayer(move, *this)};
  const Color enemy{player == Color::White ? Color::Black : Color::White};
  const auto [startPosition, endPosition] = move;
  const Cell originalStart = m_cells[startPosition.first][startPosition.second];
  const Cell originalEnd = m_cells[endPosition.first][endPosition.second];
  // make the move
  m_cells[startPosition.first][startPosition.second] = Cell();
  m_cells[endPosition.first][endPosition.second] = originalStart;
  //
  const Position kingPosition{findKing(player)};
  const auto [potentialDiagonalChecks, potentialHorizontalOrVerticalChecks,
              potentialKnightChecks] =
      getPotentialCheckPositions(*this, player);
  const bool checkedDiagonally =
      canBeCheckedByBishopOrQueen(potentialDiagonalChecks, *this, enemy);
  const bool checkedHorizontallyOrVertically = canBeCheckedByRookOrQueen(
      potentialHorizontalOrVerticalChecks, *this, enemy);
  const bool checkedByKnights =
      canBeCheckedByKnight(potentialKnightChecks, *this, enemy);
  const bool checkedByPawns =
      canBeCheckedByPawn(*this, kingPosition, player, enemy);

  // undo the move
  m_cells[startPosition.first][startPosition.second] = originalStart;
  m_cells[endPosition.first][endPosition.second] = originalEnd;
  //
  return checkedDiagonally || checkedHorizontallyOrVertically ||
         checkedByKnights || checkedByPawns;
}

auto Board::findKing(Color color) const -> Position {
  for (int x = 0; x < getWidth(); x++) {
    for (int y = 0; y < getHeight(); y++) {
      if (hasPiece<King>({x, y}, color)) {
        return {x, y};
      }
    }
  }
  std::string colorString = color == Color::White ? "White" : "Black";
  throw new std::runtime_error("Board state is invalid as there is no " +
                               colorString + "King.");
}

auto Board::scanPieces(BoardScanCallback callback) -> void {
  for (int x = 0; x < getWidth(); x++) {
    for (int y = 0; y < getHeight(); y++) {
      if (hasPiece({x, y})) {
        callback(*const_cast<PieceVariant*>(m_cells[x][y].getPiece()), {x, y});
      }
    }
  }
}

auto Board::movePiece(const PieceVariant& piece, Move move) -> void {
  const auto [startPosition, endPosition] = move;
  setPiece(endPosition, piece);
  setPiece(startPosition, std::nullopt);
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
  const std::string horizontal_line = "  +---+---+---+---+---+---+---+---+\n";
  os << horizontal_line;
  for (int rank = 0; rank < board.m_cells.size(); ++rank) {
    os << (8 - rank) << " ";
    for (const Cell& cell : board.m_cells[rank]) {
      os << "| " << cell << " ";
    }
    os << "|\n";
    os << horizontal_line;
  }
  os << "    A   B   C   D   E   F   G   H\n";
  return os;
}

}  // namespace chess