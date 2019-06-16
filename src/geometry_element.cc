#include "../include/geometry_element.h"

namespace valgo {

LatexCode GeometryElement::draw_label() const {
	std::stringstream ret;
	if (!_label.empty()) {
		ret << " node[anchor=north west] {" << _label << "}";
	}

	return ret.str();
}

GeometryElement& GeometryElement::set_color(Color color) {
	_color = color;
	return *this;
}

LatexCode GeometryElement::draw_color(double fill_opacity) const {
	std::stringstream ret;
	if ((int)_color.r_ != 0 || (int)_color.g_ != 0 || (int)_color.b_ != 0) {
		ret << ", draw={rgb:red," << (int)_color.r_ << ";green," << (int)_color.g_ << ";blue," << (int)_color.b_
		    << "}";
		ret << ", fill={rgb:red," << (int)_color.r_ << ";green," << (int)_color.g_ << ";blue," << (int)_color.b_
		    << "}";
		ret << ", fill opacity=" << fill_opacity << ", text opacity=1";
	}
	return ret.str();
}

GeometryElement& GeometryElement::set_label(std::string label) {
	_label = label;
	return *this;
}

} // namespace valgo