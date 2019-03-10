#pragma once

#include "slide_element.h"

#include <vector>

namespace valgo {

template<class T>
class Array2DElement : public SlideElement {
private:
	size_t n_, m_;
	std::vector<T> vec_; // n_ x m_

public:
	Array2DElement() = default;
	
	virtual std::unique_ptr<SlideElement> clone() const override;
	
	void resize(size_t n, size_t m) { vec_.resize(n * m); }

	void set_elem(size_t i, size_t j, T val) {
		vec_[i * m_ + j] = std::move(val);
	}

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

} // namespace valgo
