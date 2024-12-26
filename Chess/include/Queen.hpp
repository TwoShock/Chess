#pragma once
#include "Piece.hpp"
#include "IDisplay.hpp"
#include "utils.hpp"

#include <string>
namespace chess {
	class Queen : public Piece, public IDisplay {
	public:
		Queen(Color color) :Piece(color) {}

		auto display()const->std::string override {
			return pieceDisplayHelper(getColor(), 'q');
		}

	};
}
