#include <gtest/gtest.h>
#include <Board.hpp>
#include <Cell.hpp>
#include <GameManager.hpp>
#include <Turn.hpp>
#include "TestUtilities.hpp"

#include <ostream>

using namespace chess;
TEST(GameManagerTest, WhenAnInvalidMoveIsMade_EnsureGameStateDoesNotChange) {
  GameManager gameManager{Board{}};
  const Move emptySquareMove{{5, 2}, {4, 3}};
  const Move enemySquareMove{{1, 1}, {1, 2}};
  const Move illegalMove{{6, 2}, {0, 0}};

  EXPECT_EQ(GameError::CanNotMoveEmptyCell,
            gameManager.playTurn(emptySquareMove).error());
  EXPECT_EQ(Turn::White, gameManager.getCurrentTurn());
  EXPECT_EQ(GameError::CanNotMoveEnemyPiece,
            gameManager.playTurn(enemySquareMove).error());
  EXPECT_EQ(Turn::White, gameManager.getCurrentTurn());
  EXPECT_EQ(GameError::InvalidMove, gameManager.playTurn(illegalMove).error());
  EXPECT_EQ(Turn::White, gameManager.getCurrentTurn());
}

TEST(GameManagerTest, WhenPlayingLegalMoves_ExpectBoardStateToChange) {
  GameManager gameManager{Board{}};
  const Board& board{gameManager.getBoard()};
  const Move moveWhiteKnight{{7, 1}, {5, 2}};
  const Move moveBlackKnight{{0, 1}, {2, 2}};
  EXPECT_EQ(Turn::White, gameManager.getCurrentTurn());
  gameManager.playTurn(moveWhiteKnight);
  EXPECT_TRUE(board.hasPiece<Knight>(moveWhiteKnight.second, Color::White));
  EXPECT_FALSE(board.hasPiece<Knight>(moveWhiteKnight.first, Color::White));
  EXPECT_EQ(Turn::Black, gameManager.getCurrentTurn());
  gameManager.playTurn(moveBlackKnight);
  EXPECT_TRUE(board.hasPiece<Knight>(moveBlackKnight.second, Color::Black));
  EXPECT_FALSE(board.hasPiece<Knight>(moveBlackKnight.first, Color::Black));
  EXPECT_EQ(Turn::White, gameManager.getCurrentTurn());
}

TEST(GameManagerTest, AfterPawnMakesADoubleFirstMove_EnsureItCannotDoItAgain) {
  GameManager gameManager{Board{}};
  const Board& board{gameManager.getBoard()};
  const Move moveWhitePawn{{6, 0}, {4, 0}};
  const Move dummyBlackMove{{1, 7}, {3, 7}};
  const Position endingPositionForWhitePawn{moveWhitePawn.second};

  EXPECT_TRUE(board.getPiece<Pawn>(moveWhitePawn.first)->isFirstMove());
  EXPECT_EQ(Turn::White, gameManager.getCurrentTurn());
  gameManager.playTurn(moveWhitePawn);
  EXPECT_FALSE(board.getPiece<Pawn>(endingPositionForWhitePawn)->isFirstMove());
  EXPECT_EQ(Turn::Black, gameManager.getCurrentTurn());
  gameManager.playTurn(dummyBlackMove);
  EXPECT_EQ(Turn::White, gameManager.getCurrentTurn());
  const Pawn* pawn = board.getPiece<Pawn>(endingPositionForWhitePawn);
  const Moves moves = pawn->getPossibleMoves(endingPositionForWhitePawn, board);
  EXPECT_EQ(1u, moves.size());
  EXPECT_TRUE(moves.contains({endingPositionForWhitePawn, {3, 0}}));
}

TEST(GameManagerTest, EnpassantResetTests) {
  GameManager gameManager{Board{}};
  const Board& board{gameManager.getBoard()};
  const Move moveWhitePawn{{6, 0}, {4, 0}};
  const Move dummyBlackMove{{1, 7}, {3, 7}};
  const Position endingPositionForWhitePawn{moveWhitePawn.second};

  EXPECT_TRUE(board.getPiece<Pawn>(moveWhitePawn.first)->isFirstMove());
  EXPECT_EQ(Turn::White, gameManager.getCurrentTurn());
  gameManager.playTurn(moveWhitePawn);
  EXPECT_FALSE(board.getPiece<Pawn>(endingPositionForWhitePawn)->isFirstMove());
  EXPECT_EQ(Turn::Black, gameManager.getCurrentTurn());
  gameManager.playTurn(dummyBlackMove);
  EXPECT_EQ(Turn::White, gameManager.getCurrentTurn());
  const Pawn* pawn = board.getPiece<Pawn>(endingPositionForWhitePawn);
  const Moves moves = pawn->getPossibleMoves(endingPositionForWhitePawn, board);
  EXPECT_EQ(1u, moves.size());
  EXPECT_TRUE(moves.contains({endingPositionForWhitePawn, {3, 0}}));
}

TEST(
    GameManagerTest,
    GivenABlackPawnThatCanBeCapturedByEnpassant_IfWhiteDoesNotCapture_EnsureCanBeCapturedByEnpassantStatusIsSetToFalse) {
  GameManager gameManager{Board{}};
  const Board& board{gameManager.getBoard()};
  const Move firstWhiteMove{{6, 0}, {4, 0}};
  const Move secondWhiteMove{{4, 0}, {3, 0}};
  const Move thirdWhiteMove{{6, 7}, {4, 7}};

  const Move firstBlackMove{{1, 7}, {3, 7}};
  const Move secondBlackMove{{1, 1}, {3, 1}};
  const Move thirdBlackMove{{1, 1}, {3, 1}};

  gameManager.playTurn(firstWhiteMove);
  gameManager.playTurn(firstBlackMove);
  gameManager.playTurn(secondWhiteMove);
  gameManager.playTurn(thirdBlackMove);

  EXPECT_EQ(Turn::White, gameManager.getCurrentTurn());
  const Moves moves = board.getPiece<Pawn>(secondWhiteMove.second)
                          ->getPossibleMoves(secondWhiteMove.second, board);
  EXPECT_EQ(2u, moves.size());
  EXPECT_TRUE(moves.contains({secondWhiteMove.second, {2, 0}}));
  EXPECT_TRUE(moves.contains({secondWhiteMove.second, {2, 1}}));
  const Pawn* blackPawnThatCanBeCapturedByEnpassant{
      board.getPiece<Pawn>(thirdBlackMove.second)};
  EXPECT_TRUE(blackPawnThatCanBeCapturedByEnpassant->canBeTakenByEnpassant());
  gameManager.playTurn(thirdWhiteMove);
  EXPECT_FALSE(blackPawnThatCanBeCapturedByEnpassant->canBeTakenByEnpassant());
}

TEST(GameManagerTest, PawnPromotionTest) {
  const std::vector<std::vector<Cell>> intialBoardState{
      // clang-format off
/*0                                       1                         2                        3                          4                          5                           6                                 7*/
{Cell(),                     Cell(),                     Cell(),                     Cell(King(Color::Black)), Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(Pawn(Color::White)),   Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//3
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//4
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//5
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//5
{Cell(),                     Cell(),                     Cell(),                     Cell(King(Color::White)), Cell(),                     Cell(),                     Cell(),                     Cell()}//7
      // clang-format on
  };
  GameManager gameManager{Board{intialBoardState}};
  const Position pawnStartPosition{1, 0};
  const Position pawnEndPosition{0, 0};
  gameManager.setPrePromotionChoiceResponseCallback(
      [pawnEndPosition](const Board& board) {
        EXPECT_TRUE(board.hasPiece<Pawn>(pawnEndPosition));
      });
  gameManager.setPromotionCallback(
      [&pawnEndPosition](Position pos, Color color) {
        EXPECT_EQ(pawnEndPosition, pos);
        EXPECT_EQ(Color::White, color);
        return PromotionChoice::Queen;
      });
  const Board& board{gameManager.getBoard()};
  gameManager.playTurn({pawnStartPosition, pawnEndPosition});
  EXPECT_EQ(Turn::Black, gameManager.getCurrentTurn());
  EXPECT_TRUE(board.hasPiece<Queen>(pawnEndPosition));
  const Position blackKingPosition{0, 3};
  const King* king = board.getPiece<King>(blackKingPosition);
  const Moves moves = king->getPossibleMoves(blackKingPosition, board);
  EXPECT_EQ(3u, moves.size());
}

TEST(GameManagerTest, GivenCheckMateSituation_ExpectGameMangerToDetectIt) {
  const std::vector<std::vector<Cell>> intialBoardState{
      // clang-format off
/*0                                       1                         2                        3                          4                          5                           6                                 7*/
{Cell(Queen(Color::White)),  Cell(),                     Cell(),                     Cell(King(Color::Black)), Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(Queen(Color::White)),  Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//3
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//4
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//5
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//5
{Cell(),                     Cell(),                     Cell(),                     Cell(King(Color::White)), Cell(),                     Cell(),                     Cell(),                     Cell()}//7
      // clang-format on
  };
  GameManager gameManager{Board{intialBoardState}};
  gameManager.switchTurn();
  EXPECT_TRUE(gameManager.isCheckMate());
  EXPECT_FALSE(gameManager.isStaleMate());
}

TEST(GameManagerTest, GivenNoCheckMate_ExpectGameMangerToDetectIt) {
  const std::vector<std::vector<Cell>> intialBoardState{
      // clang-format off
/*0                                       1                         2                        3                          4                          5                           6                                 7*/
{Cell(),                     Cell(),                     Cell(),                     Cell(King(Color::Black)), Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(Queen(Color::White)),  Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//3
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//4
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//5
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//5
{Cell(),                     Cell(),                     Cell(),                     Cell(King(Color::White)), Cell(),                     Cell(),                     Cell(),                     Cell()}//7
      // clang-format on
  };
  GameManager gameManager{Board{intialBoardState}};
  gameManager.switchTurn();
  EXPECT_FALSE(gameManager.isCheckMate());
  EXPECT_FALSE(gameManager.isStaleMate());
}

TEST(GameManagerTest, GivenStaleMateSituation_ExpectGameMangerToDetectIt) {
  const std::vector<std::vector<Cell>> intialBoardState{
      // clang-format off
/*0                                       1                         2                        3                          4                          5                           6                                 7*/
{Cell(),                     Cell(),                     Cell(),                     Cell(King(Color::Black)), Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(Queen(Color::White)),  Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//3
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//4
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//5
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//5
{Cell(),                     Cell(),                     Cell(Queen(Color::White)),  Cell(King(Color::White)), Cell(Queen(Color::White)),  Cell(),                     Cell(),                     Cell()}//7
      // clang-format on
  };
  GameManager gameManager{Board{intialBoardState}};
  gameManager.switchTurn();
  EXPECT_TRUE(gameManager.isStaleMate());
  EXPECT_FALSE(gameManager.isCheckMate());
}
// TEST(GameMangerTest, dummy) {
//   GameManager gameManager{Board{}};
//   gameManager.startGame();
// }

TEST(GameMangerTest, performCastlingTest) {
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
  GameManager gameManager{Board{intialBoardState}};
  gameManager.playTurn({{7, 4}, {7, 2}});
  gameManager.playTurn({{0, 4}, {0, 6}});
  std::stringstream ss;
  ss << gameManager.getBoard();
  EXPECT_EQ(test::readFileContents("resources/CastlingBothSides.txt"),
            ss.str());
}

TEST(GameMangerTest, performEnpassantTest) {
  const std::vector<std::vector<Cell>> intialBoardState{
      // clang-format off
/*0                                       1                         2                        3                          4                          5                           6                                 7*/
{Cell(Rook(Color::Black)),   Cell(),                     Cell(),                     Cell(),                   Cell(King(Color::Black)),   Cell(),                     Cell(),                     Cell(Rook(Color::Black))},//0
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//1
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//2
{Cell(),                     Cell(),                     Cell(Pawn(Color::White)),   Cell(Pawn(Color::Black)), Cell(),                     Cell(),                     Cell(),                     Cell()},//3
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//4
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//5
{Cell(),                     Cell(),                     Cell(),                     Cell(),                   Cell(),                     Cell(),                     Cell(),                     Cell()},//6
{Cell(Rook(Color::White)),   Cell(),                     Cell(),                     Cell(),                   Cell(King(Color::White)),   Cell(),                     Cell(),                     Cell(Rook(Color::White))}//7
      // clang-format on
  };
  GameManager gameManager{Board{intialBoardState}};
  auto& board = const_cast<Board&>(gameManager.getBoard());
  const_cast<Pawn*>(board.getPiece<Pawn>({3, 3}))->setCanBeTakenByEnpassant(true);
  gameManager.playTurn({{3, 2}, {2, 3}});
  EXPECT_TRUE(board.hasPiece<Pawn>({2, 3}));
}
