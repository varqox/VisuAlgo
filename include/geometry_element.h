#pragma once

#include <string>
#include <sstream>

#include "slide_element.h"
#include "color.h"

namespace valgo {

class GeometryElement : public SlideElement {
protected:
    std::string _label;
    Color _color;

    LatexCode draw_label() const;
    LatexCode draw_color(double fill_opacity = 0.2) const;

public:
	GeometryElement() = default;
    GeometryElement& set_color(Color color);
    GeometryElement& set_label(std::string label);
};

} // namespace valgo