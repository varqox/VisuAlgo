#pragma once

#include "slide_element.h"

namespace valgo {

class LatexElement : public SlideElement {
private:
	std::string latex_;

public:
	LatexElement() = default;

	explicit LatexElement(std::string latex) noexcept;

	virtual std::unique_ptr<SlideElement> clone() const override;

	// Returns *this to allow chaining
	LatexElement& set(std::string latex) noexcept;

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

} // namespace valgo
