#pragma once
#include <Move.hpp>
namespace chess {
class Board;
[[nodiscard]] auto filterValidMoves(Moves moves, const Board& board) -> Moves;
}  // namespace chess
