#pragma once

#include "image.h"
#include "slide_element.h"
#include <sstream>
#include <vector>

namespace valgo {

class ImageSet : public SlideElement {
private:
	std::vector<Image> _vec;

public:
	ImageSet() = default;

	virtual std::unique_ptr<SlideElement> clone() const override;

	ImageSet& add_image(Image im);

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

} // namespace valgo