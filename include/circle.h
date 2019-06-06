#pragma once

#include <sstream>

#include "geometry_element.h"

namespace valgo {
class Circle : public GeometryElement {
private:
    double _center_x, _center_y;
    double _radius;

public:
    Circle(double center_x, double center_y, double radius);

    Circle(double center_x, double center_y, double radius, std::string label);

    void set_center(double coord_x, double coord_y);

    void set_radius(double radius);

    virtual std::unique_ptr<SlideElement> clone() const override;

    virtual LatexCode draw_as_latex() const override;

    virtual HTMLCode draw_as_html() const override;

};

} // namespace valgo