#pragma once
#include "Color.hpp"
#include <utility>
#include <vector>
#include <Position.hpp>

namespace chess {
	class Board;
	class Piece {
	public:
		Piece(Color color) :m_color(color) {}
		[[nodiscard]] auto getColor()const->Color { return m_color; }
		[[nodiscard]] virtual auto getPossibleMoves(Position startPosition, const Board& board) const->std::vector<Position>;

	private:
		Color m_color;
	};

}
