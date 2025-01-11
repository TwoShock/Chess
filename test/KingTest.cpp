#include <gtest/gtest.h>
#include <Board.hpp>
#include <Cell.hpp>
#include <ostream>
#include "TestUtilities.hpp"
using namespace chess;
TEST(KingTest, movementTest) {
  const std::vector<std::vector<Cell>> intialBoardState{
      // clang-format off
/*0                                       1                         2                        3                          4                          5                           6                                 7*/
{Cell(Rook(Color::Black)),   Cell(Knight(Color::Black)), Cell(Bishop(Color::Black)), Cell(Queen(Color::Black)), Cell(King(Color::Black)),   Cell(Bishop(Color::Black)), Cell(Knight(Color::Black)), Cell(Rook(Color::Black))},//0
{Cell(Pawn(Color::Black)),   Cell(Pawn(Color::Black)),   Cell(Pawn(Color::Black)),   Cell(Pawn(Color::Black)), Cell(Pawn(Color::Black)),   Cell(Pawn(Color::Black)),   Cell(Pawn(Color::Black)),   Cell(Pawn(Color::Black))},//1
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(),                     Cell(),                     Cell(),                     Cell(Pawn(Color::Black)), Cell(),                     Cell(),                     Cell(),                     Cell()},//3
{Cell(),                     Cell(),                     Cell(King(Color::White)),   Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//4
{Cell(),                     Cell(),                     Cell(),                     Cell(Pawn(Color::White)), Cell(),                     Cell(),                     Cell(),                     Cell()},//5
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//5
{Cell(Rook(Color::White)),   Cell(Knight(Color::White)), Cell(Bishop(Color::White)), Cell(Queen(Color::White)),Cell(),                     Cell(Bishop(Color::White)), Cell(Knight(Color::White)), Cell(Rook(Color::White))}//7
      // clang-format on
  };
  Board board{intialBoardState};
  const Position centerKingPosition{4, 2};
  board.highlightMoves(centerKingPosition);
  std::stringstream ss;
  ss << board;
  const std::string expectedMovement =
      test::readFileContents("resources/KingMovementTest.txt");
  EXPECT_EQ(expectedMovement, ss.str());
}

TEST(KingTest, whiteCastlingTest) {
  const std::vector<std::vector<Cell>> intialBoardState{
      // clang-format off
/*0                                       1                         2                        3                          4                          5                           6                                 7*/
{Cell(Rook(Color::Black)),   Cell(),                     Cell(),                     Cell(),                   Cell(King(Color::Black)),   Cell(),                     Cell(),                     Cell(Rook(Color::Black))},//0
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//1
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//3
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//4
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//5
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//6
{Cell(Rook(Color::White)),   Cell(),                     Cell(),                     Cell(),                   Cell(King(Color::White)),   Cell(),                     Cell(),                     Cell(Rook(Color::White))}//7
      // clang-format on
  };
  Board board{intialBoardState};
  const Position whiteKingPosition{7, 4};
  const Position blackKingPosition{0, 4};
  board.highlightMoves(whiteKingPosition);
  std::stringstream ss;
  ss << board;
  const std::string expectedWhiteMovement =
      test::readFileContents("resources/WhiteCastlingTest.txt");
  EXPECT_EQ(expectedWhiteMovement, ss.str());

  board.highlightMoves(blackKingPosition);
  ss.str("");
  ss << board;
  const std::string expectedBlackMovement =
      test::readFileContents("resources/BlackCastlingTest.txt");
  EXPECT_EQ(expectedBlackMovement, ss.str());
}
namespace {
auto moveBishop(Board& board, Move move) -> void {
  auto [startPosition, endPosition] = move;
  board.setPiece(endPosition, *board.getPiece<Bishop>(startPosition));
  board.setPiece(startPosition, std::nullopt);
}
}  // namespace
TEST(KingTest, GivenTheirArePiecesBetweenKingAndRook_ExpectThatWeCanNotCastle) {
  const std::vector<std::vector<Cell>> intialBoardState{
      // clang-format off
/*0                                       1                         2                        3                          4                          5                           6                                 7*/
{Cell(Rook(Color::Black)),   Cell(),                     Cell(),                     Cell(),                   Cell(King(Color::Black)),   Cell(),                     Cell(),                     Cell(Rook(Color::Black))},//0
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//1
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//3
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//4
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//5
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//6
{Cell(Rook(Color::White)),   Cell(),                     Cell(),                     Cell(),                   Cell(King(Color::White)),   Cell(Bishop(Color::White)), Cell(),                     Cell(Rook(Color::White))}//7
      // clang-format on
  };
  Board board{intialBoardState};
  const Position whiteKingPosition{7, 4};
  const Position bishopStartPosition{7, 5};
  board.highlightMoves(whiteKingPosition);
  std::stringstream ss;
  ss << board;
  const std::string expectedWhiteMovement = test::readFileContents(
      "resources/BlockedWhiteCastlingKingSideDueToBishop.txt");
  EXPECT_EQ(expectedWhiteMovement, ss.str());
  moveBishop(board, {bishopStartPosition, {7, 6}});
  ss.str("");
  board.highlightMoves(whiteKingPosition);
  ss << board;
  EXPECT_EQ(
      test::readFileContents(
          "resources/BlockedWhiteCastlingKingSideDueToBishopTwoTilesOver.txt"),
      ss.str());

  moveBishop(board, {{7, 6}, {7, 3}});
  ss.str("");
  board.highlightMoves(whiteKingPosition);
  ss << board;
  EXPECT_EQ(test::readFileContents(
                "resources/"
                "BlockedWhiteCastlingQueenSideDueToBishopInQueensPosition.txt"),
            ss.str());

  moveBishop(board, {{7, 3}, {7, 2}});
  ss.str("");
  board.highlightMoves(whiteKingPosition);
  ss << board;
  EXPECT_EQ(
      test::readFileContents(
          "resources/BlockedWhiteCastlingQueenSideDueToBishopTwoTilesOver.txt"),
      ss.str());

  moveBishop(board, {{7, 2}, {7, 1}});
  ss.str("");
  board.highlightMoves(whiteKingPosition);
  ss << board;
  EXPECT_EQ(test::readFileContents(
                "resources/"
                "BlockedWhiteCastlingQueenSideDueToBishopThreeTilesOver.txt"),
            ss.str());
}

TEST(KingTest, GivenTheKingHasMoved_ExpectCanNotCastle) {
  const std::vector<std::vector<Cell>> intialBoardState{
      // clang-format off
/*0                                       1                         2                        3                          4                          5                           6                                 7*/
{Cell(Rook(Color::Black)),   Cell(),                     Cell(),                     Cell(),                   Cell(King(Color::Black)),   Cell(),                     Cell(),                     Cell(Rook(Color::Black))},//0
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//1
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//3
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//4
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//5
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//6
{Cell(Rook(Color::White)),   Cell(),                     Cell(),                     Cell(),                   Cell(King(Color::White)),   Cell(),                     Cell(),                     Cell(Rook(Color::White))}//7
      // clang-format on
  };
  Board board{intialBoardState};
  const Position whiteKingPosition{7, 4};
  King* king = const_cast<King*>(board.getPiece<King>(whiteKingPosition));
  king->setHasMoved(true);

  board.highlightMoves(whiteKingPosition);
  std::stringstream ss;
  ss << board;
  const std::string expectedWhiteMovement =
      test::readFileContents("resources/CanNotCastleGivenKingHasMoved.txt");
  EXPECT_EQ(expectedWhiteMovement, ss.str());
}

TEST(KingTest, GivenTheRooksHaveMoved_ExpectKingCanNotCastle) {
  const std::vector<std::vector<Cell>> intialBoardState{
      // clang-format off
/*0                                       1                         2                        3                          4                          5                           6                                 7*/
{Cell(Rook(Color::Black)),   Cell(),                     Cell(),                     Cell(),                   Cell(King(Color::Black)),   Cell(),                     Cell(),                     Cell(Rook(Color::Black))},//0
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//1
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//3
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//4
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//5
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//6
{Cell(Rook(Color::White)),   Cell(),                     Cell(),                     Cell(),                   Cell(King(Color::White)),   Cell(),                     Cell(),                     Cell(Rook(Color::White))}//7
      // clang-format on
  };
  Board board{intialBoardState};
  const Position whiteKingPosition{7, 4};
  const Position rightWhiteRookPosition{7, 7};
  const Position leftWhiteRookPosition{0, 7};
  Rook* rightRook =
      const_cast<Rook*>(board.getPiece<Rook>(rightWhiteRookPosition));
  Rook* leftRook =
      const_cast<Rook*>(board.getPiece<Rook>(leftWhiteRookPosition));
  rightRook->setHasMoved(true);
  leftRook->setHasMoved(true);

  board.highlightMoves(whiteKingPosition);
  std::stringstream ss;
  ss << board;
  const std::string expectedWhiteMovement =
      test::readFileContents("resources/CanNotCastleGivenRooksHaveMoved.txt");
  EXPECT_EQ(expectedWhiteMovement, ss.str());
}

TEST(KingTest, GivenTheKingIsInCheck_ExpectCanNotCastle) {
  const std::vector<std::vector<Cell>> intialBoardState{
      // clang-format off
/*0                                       1                         2                        3                          4                          5                           6                                 7*/
{Cell(Rook(Color::Black)),   Cell(),                     Cell(),                     Cell(King(Color::Black)), Cell(Queen(Color::Black)),  Cell(),                     Cell(),                     Cell(Rook(Color::Black))},//0
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//1
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//3
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//4
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//5
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//6
{Cell(Rook(Color::White)),   Cell(),                     Cell(),                     Cell(),                   Cell(King(Color::White)),   Cell(),                     Cell(),                     Cell(Rook(Color::White))}//7
      // clang-format on
  };
  Board board{intialBoardState};
  const Position whiteKingPosition{7, 4};

  board.highlightMoves(whiteKingPosition);
  std::stringstream ss;
  ss << board;
  test::writeStringToFile("resources/GivenKingInCheckExpectCanNotCastle.txt",
                          ss.str());
  const std::string expectedWhiteMovement = test::readFileContents(
      "resources/GivenKingInCheckExpectCanNotCastle.txt");
  EXPECT_EQ(expectedWhiteMovement, ss.str());
}
namespace {
auto setUpIntermediateTileCheckUseCase(Board& board, int columnNumber) -> void {
  const std::vector<std::vector<Cell>> intialBoardState{
      // clang-format off
/*0                                       1                         2                        3                          4                          5                           6                                 7*/
{Cell(Rook(Color::Black)),   Cell(),                     Cell(),                     Cell(King(Color::Black)), Cell(),                     Cell(),                     Cell(),                     Cell(Rook(Color::Black))},//0
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//1
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//3
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//4
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//5
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//6
{Cell(Rook(Color::White)),   Cell(),                     Cell(),                     Cell(),                   Cell(King(Color::White)),   Cell(),                     Cell(),                     Cell(Rook(Color::White))}//7
      // clang-format on
  };
  board.setCells(intialBoardState);
  board.setPiece({0, columnNumber}, Rook(Color::Black));
}
auto expectCanCastleKingSide(const Board& board,
                             const King* king,
                             const Position kingPosition) -> void {
  const Moves moves = king->getPossibleMoves(kingPosition, board);
  auto [x, y] = kingPosition;
  EXPECT_TRUE(moves.contains({kingPosition, {x, y + 2}}));
}
auto expectCanCastleQueenSide(const Board& board,
                              const King* king,
                              const Position kingPosition) -> void {
  const Moves moves = king->getPossibleMoves(kingPosition, board);
  auto [x, y] = kingPosition;
  EXPECT_TRUE(moves.contains({kingPosition, {x, y - 2}}));
}
auto expectCanNotCastleKingSide(const Board& board,
                                const Position kingPosition) -> void {
  const King* king = board.getPiece<King>(kingPosition);
  const Moves moves = king->getPossibleMoves(kingPosition, board);
  auto [x, y] = kingPosition;
  EXPECT_FALSE(moves.contains({kingPosition, {x, y + 2}}));
  expectCanCastleQueenSide(board, king, kingPosition);
}
auto expectCanNotCastleQueenSide(const Board& board,
                                 const Position kingPosition) -> void {
  const King* king = board.getPiece<King>(kingPosition);
  const Moves moves = king->getPossibleMoves(kingPosition, board);
  auto [x, y] = kingPosition;
  EXPECT_FALSE(moves.contains({kingPosition, {x, y - 2}}));
  expectCanCastleKingSide(board, king, kingPosition);
}
}  // namespace
TEST(KingTest, GivenAnIntermediateTileIsInCheck_ExpectKingCannotCastle) {
  Board board;
  setUpIntermediateTileCheckUseCase(board, 5);
  const Position kingPosition{7, 4};
  expectCanNotCastleKingSide(board, kingPosition);

  setUpIntermediateTileCheckUseCase(board, 6);
  expectCanNotCastleKingSide(board, kingPosition);

  setUpIntermediateTileCheckUseCase(board, 3);
  expectCanNotCastleQueenSide(board, kingPosition);

  setUpIntermediateTileCheckUseCase(board, 2);
  expectCanNotCastleQueenSide(board, kingPosition);

  setUpIntermediateTileCheckUseCase(board, 1);
  expectCanNotCastleQueenSide(board, kingPosition);
}
