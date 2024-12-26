#pragma once

#include "Piece.hpp"
#include <Position.hpp>
#include "IDisplay.hpp"
#include"utils.hpp"

#include <string>

namespace chess {
	class Pawn :public Piece, public IDisplay {
	public:
		Pawn(Color color) :Piece(color), m_firstMove(true) {}
		auto display()const->std::string override {
			return pieceDisplayHelper(getColor(), 'p');
		}

		auto getPossibleMoves(Position startPosition, const Board& board)const->std::vector<Position> override;
	private:
		bool m_firstMove;

	};
}
