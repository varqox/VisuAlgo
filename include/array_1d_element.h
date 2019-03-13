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

	virtual std::unique_ptr<SlideElement> clone() const override;

	void set(std::vector<T> vec) noexcept;

	void resize(size_t n);

	void set_elem(size_t n, T val);

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

} // namespace valgo
