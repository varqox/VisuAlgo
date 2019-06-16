#pragma once

#include <set>
#include <sstream>

#include "circle.h"
#include "geometry_element.h"
#include "line.h"
#include "point.h"
#include "polygon.h"
#include "rectangle.h"
#include "slide_element.h"
#include "vector.h"

namespace valgo {

class Geometry : public SlideElement {
private:
	std::set<GeometryElement*> _geo_elems;
	bool _coordinate_system;
	double _xmin, _xmax, _ymin, _ymax;
	double _scale;

	LatexCode draw_coordinate_system() const;

public:
	Geometry();

	virtual std::unique_ptr<SlideElement> clone() const override;

	Geometry& add(GeometryElement& geo_elem);

	void erase(GeometryElement& goe_elem);

	void remove_all_elements();

	void set_coord_system(double xmin, double xmax, double ymin, double ymax);

	void unset_coord_system();

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

} // namespace valgo