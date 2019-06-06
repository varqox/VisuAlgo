#pragma once

#include <sstream>

#include "geometry_element.h"

namespace valgo {
class Point : public GeometryElement {
private:
    double _coord_x, _coord_y;

public:
    Point(double coord_x, double coord_y);

    Point(double coord_x, double coord_y, std::string label);

    void set_coords(double coord_x, double coord_y);

    virtual std::unique_ptr<SlideElement> clone() const override;

    virtual LatexCode draw_as_latex() const override;

    virtual HTMLCode draw_as_html() const override;

};

} // namespace valgo