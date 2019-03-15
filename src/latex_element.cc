#include "../include/latex_element.h"

namespace valgo {

LatexElement::LatexElement(std::string latex) noexcept : latex_(std::move(latex)) {}

std::unique_ptr<SlideElement> LatexElement::clone() const {
	return std::make_unique<LatexElement>(*this);
}

LatexElement& LatexElement::set(std::string latex) noexcept {
	latex_ = std::move(latex);
	return *this;
}

LatexCode LatexElement::draw_as_latex() const {
	return latex_;
}

HTMLCode LatexElement::draw_as_html() const {
	throw NotImplemented();
}

} // namespace valgo
