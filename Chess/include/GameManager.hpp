#pragma once
#include <Board.hpp>
#include <Turn.hpp>
namespace chess {

class GameManager {
 public:
  GameManager() = default;

 private:
  Board m_board;
  Turn m_turn;
};
}  // namespace chess
