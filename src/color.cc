#include "../include/color.h"

#include <iomanip>
#include <sstream>

namespace valgo {

std::string Color::to_hex() const {
	std::stringstream s;
	s << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << (int)r_ << std::setw(2)
	  << std::setfill('0') << (int)g_ << std::setw(2) << std::setfill('0') << (int)b_;
	return s.str();
}

void Color::set(uint8_t r, uint8_t g, uint8_t b) {
	r_ = r;
	g_ = g;
	b_ = b;
}

Color contrast_color(const Color& col) {
	return col.r_ * 0.299 + col.g_ * 0.587 + col.b_ * 0.114 < 128 ? Color::WHITE : Color::BLACK;
}

} // namespace valgo
