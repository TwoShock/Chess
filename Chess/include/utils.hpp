#pragma once
#include <string>
#include "Color.hpp"
namespace chess {
// displays piece on board based on color. White is uppercase letters black
// lower case.
auto pieceDisplayHelper(Color color, char representation) -> std::string;
}  // namespace chess
