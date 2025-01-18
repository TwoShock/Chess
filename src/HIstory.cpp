#include <History.hpp>

#include <optional>
#include <utility>
#include <vector>

namespace chess {

auto History::undo() -> std::optional<GameState> {
  if (m_past.size() <= 1) {
    return std::nullopt;
  }
  GameState state = std::move(m_past.back());
  m_past.pop_back();
  m_future.push_back(std::move(state));
  return m_past.back();
}

auto History::redo() -> std::optional<GameState> {
  if (m_future.empty()) {
    return std::nullopt;
  }
  GameState state = std::move(m_future.back());
  m_future.pop_back();
  m_past.push_back(std::move(state));
  return m_past.back();
}

auto History::clearFuture() -> void {
  m_future.clear();
}
auto History::logMove(const GameState& gameState) -> void {
  m_past.push_back(gameState);
}
}  // namespace chess
