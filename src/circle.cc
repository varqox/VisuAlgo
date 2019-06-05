#include "../include/circle.h"

namespace valgo {

LatexCode Circle::draw_as_latex() const {
    std::stringstream ret;
    ret << "\\filldraw [black, fill=white, very thick, fill opacity=0]  (";
    ret << _center_x << ", " << _center_y << ")";
    ret << " circle (" << _radius << ")";
    ret << draw_label();
    ret << ";\n";

    return ret.str();
}

std::unique_ptr<SlideElement> Circle::clone() const {
    return std::make_unique<Circle>(*this);
}

HTMLCode Circle::draw_as_html() const {
    throw NotImplemented();
}

Circle::Circle(double center_x, double center_y, double radius) {
    _center_x = center_x;
    _center_y = center_y;
    _radius = radius;
}

Circle::Circle(double center_x, double center_y, double radius, std::string label) {
    _center_x = center_x;
    _center_y = center_y;
    _radius = radius;
    _label = label;
}

void Circle::set_center(double center_x, double center_y) {
    _center_x = center_x;
    _center_y = center_y;
}

void Circle::set_radius(double radius) {
    _radius = radius;
}

void Circle::set_label(std::string label) {
    _label = label;
}

} // namespace valgo