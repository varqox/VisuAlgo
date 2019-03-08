#pragma once

#include "slide_element.h"

#include <vector>

namespace valgo {

template<class T>
class VariableElement : public Drawable {
private:
	T var_;

public:
	VariableElement() = default;

	void set(T var) { var_ = std::move(var); }

	virtual LatexCode draw_as_latex() const;

	virtual HTMLCode draw_as_html() const;
};

} // namespace valgo
