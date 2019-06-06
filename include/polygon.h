#pragma once

#include <sstream>
#include <string>
#include <vector> 

#include "geometry_element.h"

namespace valgo {
class Polygon : public GeometryElement {
private:
    std::vector<std::pair<double, double>> _vertices;

public:
    Polygon() = default;

    Polygon& add_vertex(double x, double y);

    virtual std::unique_ptr<SlideElement> clone() const override;

    virtual LatexCode draw_as_latex() const override;

    virtual HTMLCode draw_as_html() const override;

};

} // namespace valgo