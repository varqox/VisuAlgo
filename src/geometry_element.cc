#include "../include/geometry_element.h"

namespace valgo {

LatexCode GeometryElement::draw_label() const {
    std::stringstream ret;
    if (!_label.empty()) {
        ret << " node[anchor=west] {" << _label << "}"; 
    }

    return ret.str();
}


} // namespace valgo