#pragma once
#include "Piece.hpp"
#include "IDisplay.hpp"
#include "utils.hpp"

#include <string>
namespace chess {
	class King : public Piece, public IDisplay {
	public:
		King(Color color) :Piece(color) {}

		auto display()const->std::string override {
			return pieceDisplayHelper(getColor(), 'k');
		}

	};
}
