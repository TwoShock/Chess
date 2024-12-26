#include "Cell.hpp"
#include <King.hpp>
#include <Queen.hpp>
#include <Rook.hpp>
#include <Bishop.hpp>
#include <Knight.hpp>
#include <Pawn.hpp>

#include <ostream>
#include <variant>
#include <string>

namespace chess {
	Cell::Cell() :m_piece(std::nullopt) {}
	Cell::Cell(PieceVariant piece) :m_piece(std::move(piece)) {}
	auto Cell::display()const -> std::string
	{
		if (!m_piece) return " ";
		return std::visit([](const auto& piece) -> std::string {
			return piece.display();
			}, *m_piece);
	}

	std::ostream& operator<<(std::ostream& os, const Cell& cell) {
		os << cell.display();
		return os;
	}
}