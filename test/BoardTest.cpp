#include <gtest/gtest.h>
#include <Board.hpp>
#include <Cell.hpp>
#include <ostream>
#include "TestUtilities.hpp"

using namespace chess;
TEST(BoardTest, boardIsDisplayedProperlyOnStartOfGame) {
  Board board;
  std::stringstream ss;
  ss << board;

  const std::string ReachedInitialBoardState = ss.str();
  const std::string ExpectedInitialBoardState =
      test::readFileContents("resources/initial_board_state.txt");

  EXPECT_EQ(ExpectedInitialBoardState, ReachedInitialBoardState);
}
TEST(BoardTest, validPositionTest) {
  Board board;
  for (auto x = 0; x < board.getWidth(); x++) {
    for (auto y = 0; y < board.getHeight(); y++) {
      EXPECT_TRUE(board.isValidCellPosition({x, y}));
    }
  }
  EXPECT_FALSE(board.isValidCellPosition({-1, 1}));
  EXPECT_FALSE(board.isValidCellPosition({8, 7}));
  EXPECT_FALSE(board.isValidCellPosition({0, 8}));
}
