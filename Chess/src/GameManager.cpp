#include <Color.hpp>
#include <GameManager.hpp>
#include <Turn.hpp>
#include <cctype>
#include <cmath>
#include <format>
#include <iostream>
#include <utils.hpp>
namespace chess {
namespace {
auto turnToColor(Turn turn) -> Color {
  switch (turn) {
    case Turn::White: {
      return Color::White;
    }
    case Turn::Black: {
      return Color::Black;
    }
  };
}
bool isNumber(const std::string& str) {
  for (char c : str) {
    if (!std::isdigit(c)) {
      return false;
    }
  }
  return true;
}

auto defaultPromotionCallback(Position position,
                              Color pawnColor) -> PromotionChoice {
  const std::string promotionMessage = std::format(
      "What would you like to promote {} Pawn at position {} to ?\n",
      toString(pawnColor), toString(position));
  const std::string options =
      "1. Queen\n 2. Rook\n 3. Bishop\n 4. Knight\n Please select one of the "
      "choices.\n";
  const std::string invalidChoice = std::format(
      "Invalid choice please pick one of the following options.\n{}", options);
  int userChoice;
  std::string userInput;
  while (true) {
    std::getline(std::cin, userInput);
    if (isNumber(userInput)) {
      userChoice = std::stoi(userInput);
      if (userChoice > 4 || userChoice < 1) {
        std::cout << invalidChoice;
        continue;
      }
      break;
    } else {
      std::cout << invalidChoice;
    }
  }
  return static_cast<PromotionChoice>(userChoice);
}
auto defaultPrePromotionChocieResponseCallback(const Board& board) -> void {
  std::cout << board;
}
}  // namespace

GameManager::GameManager(Board board)
    : m_board(std::move(board)),
      m_turn(Turn::White),
      m_turnCounter(0),
      m_promotionCallback(defaultPromotionCallback),
      m_prePromotionChocieResponseCallback(
          defaultPrePromotionChocieResponseCallback) {}

auto GameManager::playTurn(Move move) -> std::expected<void, GameError> {
  const auto [startPosition, endPosition] = move;
  if (!m_board.hasPiece(startPosition)) {
    return std::unexpected(GameError::CanNotMoveEmptyCell);
  }
  if (m_board.hasPiece(startPosition, turnToColor(getOtherPlayersTurn()))) {
    return std::unexpected(GameError::CanNotMoveEnemyPiece);
  }
  const PieceVariant* piece = m_board.getCell(startPosition)->getPiece();
  const Moves possibleMoves = std::visit(
      [&startPosition, this](const auto& piece) {
        return piece.getPossibleMoves(startPosition, m_board);
      },
      *piece);
  if (!possibleMoves.contains(move)) {
    return std::unexpected(GameError::InvalidMove);
  }
  makeMove(move);
}

auto GameManager::switchTurn() -> void {
  switch (m_turn) {
    case Turn::White: {
      m_turn = Turn::Black;
      break;
    }
    case Turn::Black: {
      m_turn = Turn::White;
      break;
    }
  };
}
auto GameManager::getCurrentTurn() const -> Turn {
  return m_turn;
}
auto GameManager::getOtherPlayersTurn() const -> Turn {
  switch (m_turn) {
    case Turn::White: {
      return Turn::Black;
    }
    case Turn::Black: {
      return Turn::White;
    }
  };
}
auto GameManager::setPromotionCallback(PromotionCallback promotionCallback)
    -> void {
  m_promotionCallback = promotionCallback;
}
auto GameManager::setPrePromotionChoiceResponseCallback(
    PrePromotionChoiceResponseCallback callback) -> void {
  m_prePromotionChocieResponseCallback = callback;
}
namespace {
constexpr auto LastRowWithRespectToWhite = 0;
constexpr auto LastRowWithRespectToBlack = 7;
constexpr auto PawnTwoTileVerticalDisplacement = 2;
auto getLastRowWithRespectToCurrentPlayer(Turn turn) -> int {
  switch (turn) {
    case Turn::White: {
      return LastRowWithRespectToWhite;
    }
    case Turn::Black: {
      return LastRowWithRespectToBlack;
    }
  };
}
}  // namespace
auto GameManager::makePawnMove(Move move) -> void {
  const auto [startPosition, endPosition] = move;
  m_board.setPiece(endPosition, *m_board.getPiece<Pawn>(startPosition));
  m_board.setPiece(startPosition, std::nullopt);
  Pawn* pawn = const_cast<Pawn*>(m_board.getPiece<Pawn>(endPosition));
  if (endPosition.first ==
      getLastRowWithRespectToCurrentPlayer(getCurrentTurn())) {
    m_prePromotionChocieResponseCallback(m_board);
    PromotionChoice promotionChoice =
        m_promotionCallback(endPosition, pawn->getColor());
    promotePawn(endPosition, promotionChoice);
  }
  pawn->setIsFirstMove(false);
  if (shouldSetEnpassant(move)) {
    pawn->setCanBeTakenByEnpassant(true);
  }
}
auto GameManager::makeKingMove(Move move) -> void {
  const auto [startPosition, endPosition] = move;
  const King* king = m_board.getPiece<King>(startPosition);
  if (isCastlingMove(move)) {
    makeCastlingMove(move);
  } else {
    m_board.movePiece(*m_board.getPiece<King>(startPosition), move);
    King* king = const_cast<King*>(m_board.getPiece<King>(endPosition));
    king->setHasMoved(true);
  }
}
namespace {
auto findCastlingMoveFromMove(Move move,
                              const std::vector<CastlingMove>& castlingMoves)
    -> CastlingMove {
  CastlingMove cMove;
  for (const auto& castlingMove : castlingMoves) {
    if (castlingMove.first == move) {
      return cMove;
    }
  }
  return {};
}
}  // namespace
auto GameManager::makeCastlingMove(Move move) -> void {
  const auto [startPosition, _] = move;
  const King* king = m_board.getPiece<King>(startPosition);
  const CastlingMove castlingMove = findCastlingMoveFromMove(
      move, king->getCastlingMoves(startPosition, m_board));
  const auto [kingMove, rookMove] = castlingMove;
  {
    const King* king = m_board.getPiece<King>(kingMove.first);
    const Rook* rook = m_board.getPiece<Rook>(rookMove.first);

    m_board.movePiece(*king, kingMove);
    m_board.movePiece(*rook, rookMove);
  }
  {
    King* king = const_cast<King*>(m_board.getPiece<King>(kingMove.second));
    Rook* rook = const_cast<Rook*>(m_board.getPiece<Rook>(rookMove.second));
    king->setHasCastled(true);
    king->setHasMoved(true);
    rook->setHasMoved(true);
  }
}

auto GameManager::isCastlingMove(Move move) const -> bool {
  const auto [startPosition, endPosition] = move;
  const auto [xStart, yStart] = startPosition;
  const auto [xEnd, yEnd] = endPosition;
  return std::abs(yStart - yEnd) == 2;
}

// makeMove is called under the assumption that the move is valid and can be
// made
auto GameManager::makeMove(Move move) -> void {
  const auto [startPosition, endPosition] = move;
  const PieceVariant* pieceVariant = m_board.getCell(startPosition)->getPiece();

  std::visit(
      [this, &move, &startPosition, &endPosition](const auto& piece) {
        using T = std::decay_t<decltype(piece)>;
        if (std::is_same_v<T, Pawn>) {
          makePawnMove(move);
        } else if (std::is_same_v<T, King>) {
          makeKingMove(move);
        } else {
          m_board.movePiece(piece, move);
          if (std::is_same_v<T, Rook>) {
            const_cast<Rook*>(m_board.getPiece<Rook>(endPosition))
                ->setHasMoved(true);
          }
        }
      },
      *pieceVariant);
  switchTurn();
  setEnpassantStatusToFalseForAllPawns(getCurrentTurn());
}
auto GameManager::promotePawn(Position position,
                              PromotionChoice promotionChoice) -> void {
  switch (promotionChoice) {
    case PromotionChoice::Queen: {
      m_board.setPiece(position, Queen(turnToColor(getCurrentTurn())));
      break;
    }
    case PromotionChoice::Rook: {
      m_board.setPiece(position, Rook(turnToColor(getCurrentTurn())));
      break;
    }
    case PromotionChoice::Bishop: {
      m_board.setPiece(position, Bishop(turnToColor(getCurrentTurn())));
      break;
    }
    case PromotionChoice::Knight: {
      m_board.setPiece(position, Knight(turnToColor(getCurrentTurn())));
      break;
    }
  }
}
auto GameManager::shouldSetEnpassant(Move move) const -> bool {
  const auto [startPositon, endPosition] = move;
  return std::abs(startPositon.first - endPosition.first) ==
         PawnTwoTileVerticalDisplacement;
}
auto GameManager::setEnpassantStatusToFalseForAllPawns(Turn player) -> void {
  m_board.scanPieces(
      [&player, this](PieceVariant& pieceVariant, Position position) {
        bool isPlayerPawn = std::holds_alternative<Pawn>(pieceVariant) &&
                            m_board.hasPiece(position, turnToColor(player));
        if (isPlayerPawn) {
          Pawn* pawn = const_cast<Pawn*>(m_board.getPiece<Pawn>(position));
          pawn->setCanBeTakenByEnpassant(false);
        }
      });
}
auto GameManager::getBoard() const -> const Board& {
  return m_board;
}
}  // namespace chess