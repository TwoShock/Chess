#pragma once
#include <string>
namespace chess {
enum class Turn { White, Black };
[[nodiscard]] auto toString(Turn turn) -> std::string;
}  // namespace chess
