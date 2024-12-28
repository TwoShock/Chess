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
