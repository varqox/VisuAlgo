#include "../include/latex.h"

namespace valgo {

Latex::Latex(std::string latex) noexcept : latex_(std::move(latex)) {}

std::unique_ptr<SlideElement> Latex::clone() const {
	return std::make_unique<Latex>(*this);
}

Latex& Latex::set(std::string latex) noexcept {
	latex_ = std::move(latex);
	return *this;
}

LatexCode Latex::draw_as_latex() const {
	return latex_;
}

HTMLCode Latex::draw_as_html() const {
	throw NotImplemented();
}

} // namespace valgo
