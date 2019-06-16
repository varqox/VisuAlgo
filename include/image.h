#pragma once

#include "slide_element.h"
#include <sstream>

namespace valgo {

class Image : public SlideElement {
private:
	std::string _path;
	std::string _name;
	double _width;
	double _height;
	int _angle;
	double _right_shift;
	double _top_shift;

public:
	Image(std::string path, std::string name);

	virtual std::unique_ptr<SlideElement> clone() const override;

	// set width of image in cm
	Image& set_width(double witdh);

	// set height of image in cm
	Image& set_height(double height);

	// set rotation angle in degrees
	Image& set_angle(int angle);

	// set horizontal shift (default position is center of the page)
	Image& set_right_shift(double val);

	// set vertical shift (default position is center of the page)
	Image& set_top_shift(double val);

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

} // namespace valgo