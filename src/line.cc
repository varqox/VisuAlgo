#include "../include/line.h"

namespace valgo {

Line::Line(double begin_x, double begin_y, double end_x, double end_y) : _begin_x(begin_x), _begin_y(begin_y), _end_x(end_x), _end_y(end_y) {}

LatexCode Line::draw_as_latex() const {
    std::stringstream ret;
    ret << "\\draw [black] ";
    ret << "(" << _begin_x << ", " << _begin_y << ")";
    ret << " -- ";
    ret << "(" << _end_x << ", " << _end_y << ");\n";
    return ret.str();
}

std::unique_ptr<SlideElement> Line::clone() const {
    return std::make_unique<Line>(*this);
}

HTMLCode Line::draw_as_html() const {
    throw NotImplemented();
}

} // namespace valgo