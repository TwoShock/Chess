#pragma once

#include "Piece.hpp"
#include "IDisplay.hpp"
#include"utils.hpp"

#include <string>

namespace chess {
	class Knight :public Piece, public IDisplay {
	public:
		Knight(Color color) :Piece(color) {}
		auto display()const->std::string override {
			return pieceDisplayHelper(getColor(), 'n');
		}

	};
}

