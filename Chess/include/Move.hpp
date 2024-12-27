#pragma once
#include <utility>
#include <Position.hpp>
#include <unordered_set>
namespace chess {
	using Move = std::pair<Position, Position>;
	struct MoveHash {
		std::size_t operator()(const Move& move) const {
			PositionHash hash;
			size_t firstHash = hash(move.first);
			size_t secondHash = hash(move.second);
			return firstHash ^ (secondHash << 1);
		}
	};
	using Moves = std::unordered_set<Move, MoveHash>;
	auto mergeMoveSets(std::initializer_list<Moves> moves) -> Moves;

}
