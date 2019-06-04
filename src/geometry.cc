#include "../include/geometry.h"

namespace valgo {

LatexCode Geometry::draw_as_latex() const {
    std::stringstream ret;
    ret << "\\begin{center}\\begin{tikzpicture}\n";
    for (auto elem : _geo_elems) {
        ret << elem->draw_as_latex();
    }
    ret << "\\end{tikzpicture}\\end{center}\n";
    
    return ret.str();
}

void Geometry::add_elem(GeometryElement& geo_elem) {
    _geo_elems.emplace_back(&geo_elem);
}

std::unique_ptr<SlideElement> Geometry::clone() const {
    return std::make_unique<Geometry>(*this);
}

HTMLCode Geometry::draw_as_html() const {
    throw NotImplemented();
}

} // namespace valgo