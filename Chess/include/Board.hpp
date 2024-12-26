#pragma once
#include "Cell.hpp"
#include <vector>
#include "Position.hpp"
namespace chess {
	constexpr auto BoardSize = 8;
	class Board {
	public:
		Board();
		[[nodiscard]] auto getWidth()const -> size_t { return BoardSize; }
		[[nodiscard]] auto getHeight()const -> size_t { return BoardSize; }
		auto getCell(Position position)const->const Cell&;

		friend std::ostream& operator<<(std::ostream& os, const Board& cell);
	private:
		auto isValidCellPosition(Position position)const -> bool;
		std::vector<std::vector<Cell>> m_cells;
	};
}
