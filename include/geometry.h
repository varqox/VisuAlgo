#pragma once

#include <vector>
#include <sstream>

#include "slide_element.h"
#include "geometry_element.h"
#include "point.h"
#include "line.h"



namespace valgo {

class Geometry : public SlideElement {
private:
	std::vector<GeometryElement*> _geo_elems;

public:
	Geometry() = default;

	virtual std::unique_ptr<SlideElement> clone() const override;

	void add_elem(GeometryElement& geo_elem);

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

}