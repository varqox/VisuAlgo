#pragma once

#include "slide_element.h"

#include <vector>

namespace valgo {

template<class T>
class Array1DElement : public SlideElement {
private:
	std::vector<T> vec_;

public:
	Array1DElement() = default;

	void set(std::vector<T> vec) noexcept { vec_ = std::move(vec); }

	void resize(size_t n) { vec_.resize(n); }

	void set_elem(size_t n, T val) { vec_[n] = std::move(val); }

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

} // namespace valgo
