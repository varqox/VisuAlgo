#pragma once

#include "slide_element.h"

#include <vector>

namespace valgo {

class Slide : public Drawable {
private:
	std::vector<SlideElement> elems_;

public:
	Slide() = default;

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

} // namespace valgo
