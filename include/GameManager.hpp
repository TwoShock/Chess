#pragma once
#include <Board.hpp>
#include <History.hpp>
#include <Turn.hpp>

#include <expected>
#include <functional>
#include <unordered_map>
#include <variant>
#include <vector>

namespace chess {
enum class GameError { CanNotMoveEmptyCell, CanNotMoveEnemyPiece, InvalidMove };
enum class PromotionChoice { Queen = 1, Rook = 2, Bishop = 3, Knight = 4 };
using EnpassantMap = std::unordered_map<Position, int>;
using PromotionCallback = std::function<PromotionChoice(Position, Color)>;
using PrePromotionChoiceResponseCallback = std::function<void(const Board&)>;
[[nodiscard]] auto toString(GameError) -> std::string;
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
  auto undoMove() -> void;
  auto redoMove() -> void;
  auto startGame() -> void;

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
  auto movePrompt() const -> void;
  auto printBoard() const -> void;
  auto isInvalidMove(Move move) const -> std::optional<GameError>;
  enum class MoveCommand { Undo, Redo, Quit, Move };
  auto toMoveCommand(std::string moveInput) -> MoveCommand;

  mutable Board m_board;
  Turn m_turn;
  int m_turnCounter;
  PromotionCallback m_promotionCallback;
  PrePromotionChoiceResponseCallback m_prePromotionChocieResponseCallback;
  History m_history;
};
}  // namespace chess
