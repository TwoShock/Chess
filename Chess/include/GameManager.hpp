#pragma once
#include <Board.hpp>
#include <Turn.hpp>
#include <expected>
#include <functional>
#include <unordered_map>
#include <variant>
namespace chess {
enum class GameError { CanNotMoveEmptyCell, CanNotMoveEnemyPiece, InvalidMove };
enum class PromotionChoice { Queen = 1, Rook = 2, Bishop = 3, Knight = 4 };
using EnpassantMap = std::unordered_map<Position, int>;
using PromotionCallback = std::function<PromotionChoice(Position, Color)>;
using PrePromotionChoiceResponseCallback = std::function<void(const Board&)>;
class GameManager {
 public:
  GameManager(Board board);
  auto playTurn(Move move) -> std::expected<void, GameError>;
  auto switchTurn() -> void;
  [[nodiscard]] auto getCurrentTurn() const -> Turn;
  [[nodiscard]] auto getOtherPlayersTurn() const -> Turn;
  auto setPromotionCallback(PromotionCallback promotionCallback) -> void;
  auto setPrePromotionChoiceResponseCallback(PrePromotionChoiceResponseCallback)
      -> void;
  [[nodiscard]] auto getBoard() const -> const Board&;
  [[nodiscard]] auto isCheckMate() const -> bool;
  [[nodiscard]] auto isStaleMate() const -> bool;

 private:
  auto makePawnMove(Move move) -> void;
  auto makeKingMove(Move move) -> void;
  auto makeCastlingMove(Move move) -> void;
  auto isCastlingMove(Move move) const -> bool;
  auto makeMove(Move move) -> void;
  auto promotePawn(Position position, PromotionChoice promotionChoice) -> void;
  auto shouldSetEnpassant(Move move) const -> bool;
  // sets enpassant status to false for all pawns belonging to player
  auto setEnpassantStatusToFalseForAllPawns(Turn player) -> void;

  mutable Board m_board;
  Turn m_turn;
  int m_turnCounter;
  PromotionCallback m_promotionCallback;
  PrePromotionChoiceResponseCallback m_prePromotionChocieResponseCallback;
};
}  // namespace chess
