#include "../include/point.h"

namespace valgo {

Point::Point(double coord_x, double coord_y) : _coord_x(coord_x), _coord_y(coord_y) {}

LatexCode Point::draw_as_latex() const {
    std::stringstream ret;
    ret << "\\filldraw [black] (";
    ret << _coord_x << ", " << _coord_y << ")";
    ret << " circle (2pt)";
    ret << draw_label();
    ret << ";\n";

    return ret.str();
}

std::unique_ptr<SlideElement> Point::clone() const {
    return std::make_unique<Point>(*this);
}

HTMLCode Point::draw_as_html() const {
    throw NotImplemented();
}

Point::Point(double coord_x, double coord_y, std::string label) {
    _coord_x = coord_x;
    _coord_y = coord_y;
    _label = label;
}

void Point::set_coords(double coord_x, double coord_y) {
    _coord_x = coord_x;
    _coord_y = coord_y;
}

void Point::set_label(std::string label) {
    _label = label;
}

} // namespace valgo