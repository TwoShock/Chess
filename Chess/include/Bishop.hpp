#pragma once

#include "Piece.hpp"
#include "IDisplay.hpp"
#include"utils.hpp"

#include <string>

namespace chess {
	class Bishop :public Piece, public IDisplay {
	public:
		Bishop(Color color) :Piece(color) {}
		auto display()const->std::string override {
			return pieceDisplayHelper(getColor(), 'b');
		}

	};
}
