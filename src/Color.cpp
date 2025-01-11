#include <Color.hpp>
namespace chess {

auto getOppositeColor(Color color) -> Color {
  switch (color) {
    case Color::Black:
      return Color::White;
    case Color::White:
      return Color::Black;
  };
  return Color::Black;
}
auto toString(Color color) -> std::string {
  switch (color) {
    case Color::Black:
      return "Black";
    case Color::White:
      return "White";
  };
  return "White";
}
}  // namespace chess