#pragma once

#include <sstream>

#include "geometry_element.h"

namespace valgo {
class Line : public GeometryElement {
private:
    double _begin_x, _begin_y, _end_x, _end_y;

public:
    Line(double begin_x, double begin_y, double end_x, double end_y);

    virtual std::unique_ptr<SlideElement> clone() const override;

    virtual LatexCode draw_as_latex() const override;

    virtual HTMLCode draw_as_html() const override;

};

} // namespace valgo