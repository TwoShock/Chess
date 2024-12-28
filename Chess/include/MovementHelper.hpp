#pragma once
#include <Board.hpp>
#include <Move.hpp>
#include <Position.hpp>
namespace chess {
[[nodiscard]] auto getDiagonalMoves(const Piece& piece,
                      Position startPosition,
                      const Board& board) -> Moves;
[[nodiscard]] auto getVerticalAndHorizontalMoves(const Piece& piece,
                      Position startPosition,
                      const Board& board) -> Moves;
}
