#pragma once

#include <sstream>
#include <string> 

#include "geometry_element.h"

namespace valgo {
class Rectangle : public GeometryElement {
private:
    double _left_x, _left_y, _right_x, _right_y;
    
public:
    Rectangle(double left_x, double left_y, double right_x, double right_y);

    Rectangle(double left_x, double left_y, double right_x, double right_y, std::string label);

    void set_coords(double left_x, double left_y, double right_x, double right_y);

    virtual std::unique_ptr<SlideElement> clone() const override;

    virtual LatexCode draw_as_latex() const override;

    virtual HTMLCode draw_as_html() const override;

};

} // namespace valgo