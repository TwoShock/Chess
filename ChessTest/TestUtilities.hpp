#pragma once
#include <string>
#include <Board.hpp>
namespace test {
    auto readFileContents(const std::string& fileName)->std::string;
    auto createEmptyBoard() -> chess::Board;
}
