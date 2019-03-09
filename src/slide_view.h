#pragma once

#include "slide_element.h"

#include <memory>
#include <vector>

namespace valgo {

class SlideView : public Drawable {
private:
	std::vector<SlideElement*> elems_;

public:
	SlideView() = default;

	void add_element(SlideElement& elem);

	void remove_element(SlideElement& elem);

	void remove_all_elements();

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

} // namespace valgo
