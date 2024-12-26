#include "Board.hpp"
#include "Cell.hpp"
#include "Pawn.hpp"
#include <ostream>
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

	std::ostream& operator<<(std::ostream& os, const Board& board)
	{
		const std::string horizontal_line = "  +---+---+---+---+---+---+---+---+\n";
		os << horizontal_line;
		for (int rank = 0; rank < board.m_cells.size(); ++rank) {
			os << (8 - rank) << " "; 
			for (const Cell& cell : board.m_cells[rank]) {
				os << "| "<<cell<<" ";
			}
			os << "|\n";
			os << horizontal_line; 
		}
		os << "    A   B   C   D   E   F   G   H\n";
		return os;
	}


}