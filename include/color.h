#pragma once

#include <cstdint>
#include <string>

namespace valgo {

class Color {
public:
	uint8_t r_ = 0;
	uint8_t g_ = 0;
	uint8_t b_ = 0;

	Color() = default;
	Color(uint8_t r, uint8_t g, uint8_t b);

	std::string to_hex() const;


	void set(uint8_t r, uint8_t g, uint8_t b);

	static const Color black;
	static const Color red;
	static const Color green;
	static const Color blue;
	static const Color yellow;
	static const Color magenta;
	static const Color cyan;
	static const Color white;
	static const Color light_red;
	static const Color light_green;
	static const Color light_blue;
	static const Color light_yellow;
	static const Color light_brown;
};

Color contrast_color(const Color &col);

} // namespace valgo
