#include "Pawn.hpp"
#include <Board.hpp>
#include <Move.hpp>
#include <MoveValidator.hpp>

namespace chess {
	namespace {
		auto filterValidMoves(Moves moves, const Board& board) -> Moves {
			Moves validMoves;
			for (const auto& move : moves) {
				if (computeMoveStatus(move, board) == MoveStatus::Valid) {
					validMoves.insert(move);
				}
			}
			return validMoves;

		}
	}
	auto Pawn::getPossibleMoves(Position startPosition, const Board& board) const -> Moves
	{
		Moves forwardMoves{ getForwardMoves(startPosition, board) };
		Moves captureMoves{ getCaptureMoves(startPosition,board) };
		Moves allMoves{ mergeMoveSets({forwardMoves,captureMoves}) };
		return filterValidMoves(allMoves, board);
	}
	auto Pawn::getForwardMoves(Position startPosition, const Board& board) const -> Moves
	{
		auto [x, y] = startPosition;
		Moves moves;
		Move forwardOnce{ {x,y},{x + 1,y} };
		Move forwardTwice{ {x,y},{x + 2,y} };
		if (m_firstMove && !board.hasPiece({ x + 1,y }) && !board.hasPiece({ x + 2,y })) {
			moves.insert(forwardTwice);
		}
		if (!board.hasPiece({ x + 1,y })) {
			moves.insert(forwardOnce);
		}
		return moves;
	}
	auto Pawn::getCaptureMoves(Position startPosition, const Board& board) const -> Moves
	{
		auto [x, y] = startPosition;
		Moves moves;
		Move rightDiagonal{ {x,y},{x + 1,y + 1} };
		Move leftDiagonal{ {x,y},{x + 1,y - 1} };
		Color opponentColor = getOppositeColor();
		if (board.hasPiece({ x + 1,y + 1 }, opponentColor)) {
			moves.insert(rightDiagonal);
		}
		if (board.hasPiece({ x + 1,y - 1 }, opponentColor)) {
			moves.insert(leftDiagonal);
		}
		return mergeMoveSets({ getEnpassantCaptureMoves(startPosition, board),moves });
	}
	auto Pawn::getEnpassantCaptureMoves(Position startPosition, const Board& board) const -> Moves
	{
		auto [x, y] = startPosition;
		Position leftOfStart{ x ,y - 1 };
		Position rightOfStart{ x ,y + 1 };
		Color opponentColor = getOppositeColor();
		Moves moves;
		auto canPieceBeTakenByEnpassant = [&board, opponentColor](Position piecePosition) {
			if (board.hasPiece<Pawn>(piecePosition, opponentColor)) {
				const Pawn* opponentPawn = board.getPiece<Pawn>(piecePosition);
				return opponentPawn->canBeTakenByEnpassant();
			}
			return false;
			};
		if (canPieceBeTakenByEnpassant(leftOfStart)) {
			moves.insert({ startPosition,{x + 1,y - 1 } });
		}
		if (canPieceBeTakenByEnpassant(rightOfStart)) {
			moves.insert({ startPosition,{x + 1,y + 1 } });
		}
		return moves;
	}
}
