#pragma once

#include <string>
#include <sstream>

#include "slide_element.h"

namespace valgo {

class GeometryElement : public SlideElement {
protected:
    std::string _label;

    LatexCode draw_label() const;

public:
	GeometryElement() = default;
    
};

} // namespace valgo