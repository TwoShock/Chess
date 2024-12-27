#include <Color.hpp>
namespace chess {

	auto getOppositeColor(Color color) -> Color {
		switch (color) {
		case Color::Black:
			return Color::White;
		case Color::White:
			return Color::Black;
		};

	}
}