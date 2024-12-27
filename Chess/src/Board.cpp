#include "Board.hpp"
#include "Cell.hpp"
#include "Pawn.hpp"
#include <ostream>
#include <format>
namespace chess {
	Board::Board() {
		m_cells = {
			{Cell(Rook(Color::Black)),Cell(Knight(Color::Black)),Cell(Bishop(Color::Black)),Cell(Queen(Color::Black)),Cell(King(Color::Black)),Cell(Bishop(Color::Black)),Cell(Knight(Color::Black)),Cell(Rook(Color::Black))},
			{Cell(Pawn(Color::Black)),Cell(Pawn(Color::Black)),Cell(Pawn(Color::Black)),Cell(Pawn(Color::Black)),Cell(Pawn(Color::Black)),Cell(Pawn(Color::Black)),Cell(Pawn(Color::Black)),Cell(Pawn(Color::Black))},
			{Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
			{Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
			{Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
			{Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
			{Cell(Pawn(Color::White)),Cell(Pawn(Color::White)),Cell(Pawn(Color::White)),Cell(Pawn(Color::White)),Cell(Pawn(Color::White)),Cell(Pawn(Color::White)),Cell(Pawn(Color::White)),Cell(Pawn(Color::White))},
			{Cell(Rook(Color::White)),Cell(Knight(Color::White)),Cell(Bishop(Color::White)),Cell(Queen(Color::White)),Cell(King(Color::White)),Cell(Bishop(Color::White)),Cell(Knight(Color::White)),Cell(Rook(Color::White))}
		};
	}
	Board::Board(std::vector<std::vector<Cell>> initialState):m_cells(std::move(initialState))
	{
	}
	auto Board::setPiece(Position position,PieceVariant piece) -> void
	{
		if (isValidCellPosition(position)) {
			auto [x, y] = position;
			m_cells[x][y].setPiece(piece);
		}
	}
	auto Board::getCell(Position position) const -> const Cell*
	{
		auto [x, y] = position;
		if (!isValidCellPosition(position)) {
			return nullptr;
		}
		return &m_cells[x][y];
	}

	auto Board::hasPiece(Position position) const -> bool {
		const Cell* cell = getCell(position);
		return cell->getPiece() != nullptr;
	}
	auto Board::hasPiece(Position position, Color color) const -> bool
	{
		if (!hasPiece(position)) {
			return false;
		}
		const PieceVariant* piece = getCell(position)->getPiece();
		bool isSameColor = false;
		std::visit([&isSameColor,color](const auto& pieceValue) {
			isSameColor = pieceValue.getColor() == color;
			},*piece);
		return isSameColor;
	}
	auto Board::isValidCellPosition(Position position)const -> bool
	{
		auto [x, y] = position;
		if (x >= 0 && x <= getWidth() && y >= 0 && y <= getHeight()) {
			return true;
		}
		return false;
	}

	std::ostream& operator<<(std::ostream& os, const Board& board)
	{
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


}