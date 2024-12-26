#pragma once

#include "Piece.hpp"
#include "IDisplay.hpp"
#include"utils.hpp"

#include <string>

namespace chess {
	class Pawn :public Piece, public IDisplay {
	public:
		Pawn(Color color) :Piece(color) {}
		auto display()const->std::string override {
			return pieceDisplayHelper(getColor(), 'p');
		}

	};
}
