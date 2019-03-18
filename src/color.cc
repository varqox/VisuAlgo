#include "../include/color.h"

#include <sstream>
#include <iomanip>

namespace valgo {

const Color Color::black(0, 0, 0);
const Color Color::red(255, 0, 0);
const Color Color::green(0, 255, 0);
const Color Color::blue(0, 0, 255);
const Color Color::yellow(255, 255, 0);
const Color Color::magenta(255, 0, 255);
const Color Color::cyan(0, 255, 255);
const Color Color::white(255, 255, 255);

const Color Color::light_red(255, 105, 97);
const Color Color::light_green(192, 216, 144);
const Color Color::light_blue(175, 238, 238);
const Color Color::light_yellow(255, 255, 128);
const Color Color::light_brown(150, 90, 50);

Color::Color(uint8_t r, uint8_t g, uint8_t b) : r_(r), g_(g), b_(b) {}

std::string Color::to_hex() const {
	std::stringstream s;
	s << std::hex
	  << std::setw(2) << std::setfill('0') << (int)r_
	  << std::setw(2) << std::setfill('0') << (int)g_
	  << std::setw(2) << std::setfill('0') << (int)b_;
	return s.str();
}

void Color::set(uint8_t r, uint8_t g, uint8_t b) {
	r_ = r;
	g_ = g;
	b_ = b;
}

Color contrast_color(const Color &col) {
	return col.r_ * 0.299 + col.g_ * 0.587 + col.b_ * 0.114 < 128 ? Color::white : Color::black;
}

} // namespace valgo
