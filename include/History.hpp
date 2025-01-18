#pragma once

#include <Board.hpp>
#include <Turn.hpp>

#include <optional>
#include <utility>
#include <vector>

namespace chess {
using GameState = std::pair<Board, Turn>;
class History {
 public:
  History() = default;
  // returns the board and turn state one move prior and pushes the existing one
  // into the future for redo
  [[nodiscard]] auto undo() -> std::optional<GameState>;

  // returns the board and turn state to one move in the future if an undo was
  // done prior and that state is pushed in the past
  [[nodiscard]] auto redo() -> std::optional<GameState>;
  auto clearFuture() -> void;
  auto logMove(const GameState& gameState) -> void;

 private:
  std::vector<GameState> m_past;
  std::vector<GameState> m_future;
};
}  // namespace chess