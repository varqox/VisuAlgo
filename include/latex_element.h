#pragma once

#include "slide_element.h"

namespace valgo {

class LatexElement : public SlideElement {
private:
	std::string latex_;

public:
	LatexElement() = default;
	
	virtual std::unique_ptr<SlideElement> clone() const override;
	
	void set(std::string latex) noexcept { latex_ = std::move(latex); }

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

} // namespace valgo