#pragma once

#include "slide_element.h"

#include <memory>
#include <vector>

namespace valgo {

class Slide : public Drawable {
private:
	std::vector<std::unique_ptr<SlideElement>> elems_;

public:
	Slide() = default;

	void add_element(SlideElement* elem);

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

} // namespace valgo
