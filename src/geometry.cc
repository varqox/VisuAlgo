#include "../include/geometry.h"

namespace valgo {

Geometry::Geometry() {
    _scale = 0.8;
    _coordinate_system = false;
}

LatexCode Geometry::draw_coordinate_system() const {
    std::stringstream ret;
    if (_coordinate_system) {
        ret << "\\tkzInit[xmax=" << _xmax <<",";
        ret << "ymax=" << _ymax <<",";
        ret << "xmin=" << _xmin <<",";
        ret << "ymin=" << _ymin <<"]\n";

        ret << "\\tkzGrid\n";
        ret << "\\tkzAxeXY\n";
    }

    return ret.str();
}

LatexCode Geometry::draw_as_latex() const {
    std::stringstream ret;
   
    ret << "\\begin{center}\n";
    ret << "\\resizebox{!}{" << _scale << "\\textheight}{%\n";
    ret << "\\begin{tikzpicture}\n";
    
    ret << draw_coordinate_system();

    for (auto elem : _geo_elems) {
        ret << elem->draw_as_latex();
    }
    ret << "\\end{tikzpicture}\n";
    ret << "}\n";
    ret << "\\end{center}\n";
    
    return ret.str();
}

Geometry& Geometry::add(GeometryElement& geo_elem) {
    _geo_elems.insert(&geo_elem);
    return *this;
}

void Geometry::erase(GeometryElement& geo_elem) {
    _geo_elems.erase(&geo_elem);
}

void Geometry::remove_all_elements() {
    _geo_elems.clear();
}

void Geometry::set_coord_system(double xmin, double xmax, double ymin, double ymax) {
    _xmin = xmin;
    _xmax = xmax;
    _ymin = ymin;
    _ymax = ymax;
    _coordinate_system = true;
}

void Geometry::unset_coord_system() {
    _coordinate_system = false;
}

std::unique_ptr<SlideElement> Geometry::clone() const {
    return std::make_unique<Geometry>(*this);
}

HTMLCode Geometry::draw_as_html() const {
    throw NotImplemented();
}

} // namespace valgo