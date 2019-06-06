#include "../include/polygon.h"

namespace valgo {


Polygon& Polygon::add_vertex(double x, double y) {
    _vertices.emplace_back(x, y);
    return *this;
}

LatexCode Polygon::draw_as_latex() const {
    std::stringstream ret;
    ret << "\\draw[black, ultra thick ";
    ret << draw_color() << "]";
    for (auto& p : _vertices) {
        ret << "(" << p.first << ", " << p.second << ") -- ";
    }
    ret << "cycle";
    ret << draw_label();
    ret << ";\n";

    return ret.str();
}

std::unique_ptr<SlideElement> Polygon::clone() const {
    return std::make_unique<Polygon>(*this);
}

HTMLCode Polygon::draw_as_html() const {
    throw NotImplemented();
}


}