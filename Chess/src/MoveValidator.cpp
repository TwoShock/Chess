#include "MoveValidator.hpp"
#include <Turn.hpp>
#include <Board.hpp>
namespace chess {

	auto computeMoveStatus(Move move, const Board& board) -> MoveStatus
	{
		return MoveStatus::Valid;
	}
}
