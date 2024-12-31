#pragma once
#include <string>
namespace chess {
enum class Color { Black, White };
[[nodiscard]] auto toString(Color color) -> std::string;
}
