#pragma once
#include "Color.hpp"
#include <utility>
#include <vector>
#include <Position.hpp>
#include <Move.hpp>

namespace chess {
	class Board;
	class Piece {
	public:
		Piece(Color color) :m_color(color) {}
		virtual ~Piece() = default;
		[[nodiscard]] auto getColor()const->Color { return m_color; }
		[[nodiscard]] auto getOppositeColor()const -> Color;
		[[nodiscard]] virtual auto getPossibleMoves(Position startPosition, const Board& board) const->Moves;

	private:
		[[nodiscard]] auto isFriendly(const Piece& other)const->bool;
		[[nodiscard]] auto isEnemy(const Piece& other)const->bool;
		Color m_color;
	};

}
