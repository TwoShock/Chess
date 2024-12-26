#pragma once
#include "Piece.hpp"
#include "Cell.hpp"
#include "Pawn.hpp"

#include <vector>
namespace chess {
	constexpr auto BoardSize = 8;
	class Board {
	public:
		Board();
		[[nodiscard]] auto getWidth()->size_t { return BoardSize; }
		[[nodiscard]] auto getHeight()->size_t { return BoardSize; }

		friend std::ostream& operator<<(std::ostream& os, const Board& cell);
	private:
		std::vector<std::vector<Cell>> m_cells;
	};
}
