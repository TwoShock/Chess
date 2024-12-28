#pragma once
#include <Board.hpp>
#include <string>
namespace test {
auto readFileContents(const std::string& fileName) -> std::string;
auto createEmptyBoard() -> chess::Board;
auto writeStringToFile(const std::string& filename,
                       const std::string& content) -> void;
}  // namespace test
