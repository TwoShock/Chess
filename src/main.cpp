#include <GameManager.hpp>
#include <Board.hpp>
using namespace chess;
int main() {
  GameManager manager{Board{}};
  manager.startGame();
}