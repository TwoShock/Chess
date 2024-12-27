#pragma once
#include "Cell.hpp"
#include <vector>
#include "Position.hpp"
namespace chess {
	constexpr auto BoardSize = 8;
	class Board {
	public:
		Board();
		Board(std::vector<std::vector<Cell>> initialState);
		[[nodiscard]] auto getWidth()const -> size_t { return BoardSize; }
		[[nodiscard]] auto getHeight()const -> size_t { return BoardSize; }
		auto setPiece(Position position,PieceVariant piece) -> void;
		auto getCell(Position position)const->const Cell*;
		auto hasPiece(Position position)const ->bool;
		auto hasPiece(Position position, Color color)const -> bool;
		template<typename T>
		auto hasPiece(Position position)const ->bool {
			if (!hasPiece(position)) {
				return false;
			}
			const PieceVariant* piece = getCell(position)->getPiece();
			return std::holds_alternative<T>(*piece);
		}
		template<typename T>
		auto hasPiece(Position position, Color color)const ->bool {
			if (!hasPiece(position, color)) {
				return false;
			}
			const PieceVariant* piece = getCell(position)->getPiece();
			return std::holds_alternative<T>(*piece);
		}
		template<class T>
		auto getPiece(Position position)const->const T* {
			if (!hasPiece<T>(position)) {
				return nullptr;
			}
			const PieceVariant* piece = getCell(position)->getPiece();
			return &std::get<T>(*piece);

		}

		friend std::ostream& operator<<(std::ostream& os, const Board& cell);
	private:
		auto isValidCellPosition(Position position)const -> bool;
		std::vector<std::vector<Cell>> m_cells;
	};
}
