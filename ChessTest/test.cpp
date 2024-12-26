#include "pch.h"
#include <Board.hpp>
#include <Cell.hpp>
#include <iostream>
using namespace chess;
TEST(TestCaseName, TestName) {
	Cell c{Pawn(Color::White)};
	std::cout << c.display();

}