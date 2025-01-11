#include "utils.hpp"
#include "Color.hpp"
namespace chess {

auto pieceDisplayHelper(Color color, char representation) -> std::string {
  {
    if (color == Color::White) {
      return std::string(1, std::toupper(representation));
    }
    return std::string(1, std::tolower(representation));
  }
}

}  // namespace chess