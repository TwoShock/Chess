#include "Turn.hpp"

auto chess::toString(Turn turn) -> std::string {
  switch (turn) {
    case Turn::White: {
      return "White";
    }
    case Turn::Black: {
      return "Black";
    }
  };
}