#include "../include/vector.h"

namespace valgo {

Vector::Vector(double left_x, double left_y, double end_x, double end_y)
  : _begin_x(left_x), _begin_y(left_y), _end_x(end_x), _end_y(end_y) {}

LatexCode Vector::draw_as_latex() const {
	std::stringstream ret;
	ret << "\\draw [line width=2pt, -stealth ";
	ret << draw_color(1) << "] ";
	ret << "(" << _begin_x << ", " << _begin_y << ") ";
	ret << "-- ";
	ret << "(" << _end_x << ", " << _end_y << ") ";
	ret << draw_label();
	ret << ";\n";

	return ret.str();
}

std::unique_ptr<SlideElement> Vector::clone() const { return std::make_unique<Vector>(*this); }

HTMLCode Vector::draw_as_html() const { throw NotImplemented(); }

Vector::Vector(double begin_x, double begin_y, double end_x, double end_y, std::string label)
  : _begin_x(begin_x), _begin_y(begin_y), _end_x(end_x), _end_y(end_y) {
	_label = label;
}

void Vector::set_coords(double begin_x, double begin_y, double end_x, double end_y) {
	_begin_x = begin_x;
	_begin_y = begin_y;
	_end_x = end_x;
	_end_y = end_y;
}

} // namespace valgo