#include "../include/image.h"

namespace valgo {
Image::Image(std::string path, std::string name)
  : _path(path), _name(name), _width(0), _height(0), _angle(0), _right_shift(0), _top_shift(0) {}

std::unique_ptr<SlideElement> Image::clone() const { return std::make_unique<Image>(*this); }

Image& Image::set_width(double width) {
	_width = std::move(width);
	return *this;
}

Image& Image::set_height(double height) {
	_height = std::move(height);
	return *this;
}

Image& Image::set_angle(int angle) {
	_angle = std::move(angle);
	return *this;
}

Image& Image::set_right_shift(double right_shift) {
	_right_shift = std::move(right_shift);
	return *this;
}

Image& Image::set_top_shift(double top_shift) {
	_top_shift = std::move(top_shift);
	return *this;
}

LatexCode Image::draw_as_latex() const {
	std::stringstream ret;
	ret << "\\graphicspath{ {" << _path << "} }\n";
	ret << "\\node [xshift=" << _right_shift << "cm] [yshift=" << _top_shift << "cm]";
	ret << "{\\includegraphics[height=" << _height << "cm, width=" << _width << "cm, angle = " << _angle << "]{"
	    << _name << "}};\n";
	return ret.str();
}

HTMLCode Image::draw_as_html() const { throw NotImplemented(); }
} // namespace valgo