#include "../include/latex_element.h"

namespace valgo {

std::unique_ptr<SlideElement> LatexElement::clone() const {
	return std::make_unique<LatexElement>(*this);
}

LatexCode LatexElement::draw_as_latex() const {
	return latex_;
}

HTMLCode LatexElement::draw_as_html() const {
	throw NotImplemented();
}

} // namespace valgo
