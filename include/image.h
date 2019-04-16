#pragma once

#include <sstream>
#include "slide_element.h"

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

	Image& set_width(double witdh);

	Image& set_height(double height);

	Image& set_angle(int angle);

	Image& set_right_shift(double val);

	Image& set_top_shift(double val);

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

}