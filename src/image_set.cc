#include "../include/image_set.h"

namespace valgo {

std::unique_ptr<SlideElement> ImageSet::clone() const { return std::make_unique<ImageSet>(*this); }

ImageSet& ImageSet::add_image(Image im) {
	_vec.push_back(im);
	return *this;
}

LatexCode ImageSet::draw_as_latex() const {
	std::stringstream ret;
	ret << "\\begin{center}\n\\begin{tikzpicture}[remember picture,overlay,shift={(current page.center)}]\n";

	for (size_t i = 0; i < _vec.size(); ++i)
		ret << _vec[i].draw_as_latex();

	ret << "\\end{tikzpicture}\n\\end{center}\n";

	return ret.str();
}

HTMLCode ImageSet::draw_as_html() const { throw NotImplemented(); }
} // namespace valgo