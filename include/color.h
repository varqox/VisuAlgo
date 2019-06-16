#pragma once

#include <cstdint>
#include <string>

namespace valgo {

class Color {
public:
	uint8_t r_ = 0;
	uint8_t g_ = 0;
	uint8_t b_ = 0;

	constexpr Color() = default;
	constexpr Color(uint8_t r, uint8_t g, uint8_t b) : r_(r), g_(g), b_(b) {}

	std::string to_hex() const;

	void set(uint8_t r, uint8_t g, uint8_t b);

	static const Color BLACK;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;
	static const Color YELLOW;
	static const Color MAGENTA;
	static const Color CYAN;
	static const Color WHITE;

	static const Color LIGHT_RED;
	static const Color LIGHT_GREEN;
	static const Color LIGHT_BLUE;
	static const Color LIGHT_YELLOW;
	static const Color LIGHT_BROWN;
};

Color contrast_color(const Color& col);

/****************** Implementation ******************/

constexpr Color Color::BLACK(0, 0, 0);
constexpr Color Color::RED(255, 0, 0);
constexpr Color Color::GREEN(0, 255, 0);
constexpr Color Color::BLUE(0, 0, 255);
constexpr Color Color::YELLOW(255, 255, 0);
constexpr Color Color::MAGENTA(255, 0, 255);
constexpr Color Color::CYAN(0, 255, 255);
constexpr Color Color::WHITE(255, 255, 255);

constexpr Color Color::LIGHT_RED(255, 105, 97);
constexpr Color Color::LIGHT_GREEN(192, 216, 144);
constexpr Color Color::LIGHT_BLUE(175, 238, 238);
constexpr Color Color::LIGHT_YELLOW(255, 255, 128);
constexpr Color Color::LIGHT_BROWN(150, 90, 50);

} // namespace valgo
