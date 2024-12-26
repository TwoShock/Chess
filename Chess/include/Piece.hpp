#pragma once
#include "Color.hpp"
#include <utility>
namespace chess {
	class Piece {
	public:
		Piece(Color color) :m_color(color){}
		[[nodiscard]] auto getColor()const->Color { return m_color; }
	private:
		Color m_color;
	};

}
