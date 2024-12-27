#pragma once
#include <utility>
namespace chess {
	using Position = std::pair<int, int>;
	struct PositionHash {
		std::size_t operator()(const std::pair<int, int>& p) const {
			return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
		}
	};
}
