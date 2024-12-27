#pragma once
#include <Move.hpp>
namespace chess {
	enum class MoveStatus {
		Invalid,
		Valid
	};
	class Board;
	[[nodiscard]] auto computeMoveStatus(Move move,const Board &board) -> MoveStatus;

}
