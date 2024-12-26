#pragma once
#include "Piece.hpp"
#include <optional>
#include <variant>
#include <King.hpp>
#include <Queen.hpp>
#include <Rook.hpp>
#include <Bishop.hpp>
#include <Knight.hpp>
#include <Pawn.hpp>
namespace chess {
	using PieceVariant = std::variant<King, Queen, Rook, Bishop, Knight, Pawn>;
	class Cell :public IDisplay {
	public:
		Cell();
		Cell(PieceVariant piece);
		[[nodiscard]] auto hasPiece()const->bool { return m_piece.has_value(); }
		[[nodiscard]] auto getPiece()const->const PieceVariant* {
			if (hasPiece()) {
				return &m_piece.value();
			}
			return nullptr;
		}

		[[nodiscard]] auto display()const->std::string override;
		friend std::ostream& operator<<(std::ostream& os, const Cell& cell);

	private:
		std::optional<PieceVariant> m_piece;
	};
}
