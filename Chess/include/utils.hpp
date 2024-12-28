#pragma once
#include <Color.hpp>
#include <string>
#include <unordered_set>
#include <vector>
namespace chess {
// displays piece on board based on color. White is uppercase letters black
// lower case.
auto pieceDisplayHelper(Color color, char representation) -> std::string;
}  // namespace chess
