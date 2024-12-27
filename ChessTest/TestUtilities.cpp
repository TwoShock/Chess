#include "pch.h"
#include "TestUtilities.hpp" 
#include <string>
#include <fstream>
#include <Cell.hpp>
namespace test {
	auto readFileContents(const std::string& filepath) -> std::string {
		std::ifstream file(filepath);

		if (!file.is_open()) {
			throw std::runtime_error("Failed to open file: " + filepath);
		}

		std::stringstream buffer;
		buffer << file.rdbuf();

		if (file.bad()) {
			throw std::runtime_error("Error occurred while reading file: " + filepath);
		}

		return buffer.str();
	}
	auto createEmptyBoard() -> chess::Board
	{
		using namespace chess;
		return chess::Board({
			{Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
			{Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
			{Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
			{Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
			{Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
			{Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
			{Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
			{Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
			});
	}
}
