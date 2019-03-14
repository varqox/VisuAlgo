#pragma once

#include "slide_element.h"

#include <vector>

namespace valgo {

template<class T>
class VariableElement : public SlideElement {
private:
	T var_;

public:
	VariableElement() = default;

	virtual std::unique_ptr<SlideElement> clone() const override;

	void set(T var) { var_ = std::move(var); }

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

} // namespace valgo
