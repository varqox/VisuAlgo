#include "../include/rectangle.h"

namespace valgo {

Rectangle::Rectangle(double left_x, double left_y, double right_x, double right_y) :
    _left_x(left_x), _left_y(left_y), _right_x(right_x), _right_y(right_y) {}

LatexCode Rectangle::draw_as_latex() const {
    std::stringstream ret;
    ret << "\\draw [very thick ";
    ret << draw_color() << "] ";
    ret << "(" << _left_x << ", " << _left_y << ") ";
    ret << "rectangle ";
    ret << "(" << _right_x << ", " << _right_y << ") ";
    ret << draw_label();
    ret << ";\n";

    return ret.str();
}

std::unique_ptr<SlideElement> Rectangle::clone() const {
    return std::make_unique<Rectangle>(*this);
}

HTMLCode Rectangle::draw_as_html() const {
    throw NotImplemented();
}

Rectangle::Rectangle(double left_x, double left_y, double right_x, double right_y, std::string label) : 
    _left_x(left_x), _left_y(left_y), _right_x(right_x), _right_y(right_y) {
        _label = label;
    }

void Rectangle::set_coords(double left_x, double left_y, double right_x, double right_y) {
    _left_x = left_x;
    _left_y = left_y;
    _right_x = right_x;
    _right_y = right_y;
}

} // namespace valgo