#pragma once

#include "slide_element.h"

#include <vector>

namespace valgo {

class Itemize : public SlideElement {
private:
	std::vector<std::unique_ptr<SlideElement>> elems_;

public:
	Itemize(const Itemize& be);
	Itemize& operator=(const Itemize& be);

	Itemize(Itemize&&) noexcept = default;
	Itemize& operator=(Itemize&&) noexcept = default;

	Itemize() noexcept = default;

	template <class... Elem>
	explicit Itemize(const Elem&... elems);

	std::unique_ptr<SlideElement> clone() const override;

	// Returns *this to allow chaining
	Itemize& add_item(const SlideElement& elem);

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

/****************** Implementation ******************/

template <class... Elem>
inline Itemize::Itemize(const Elem&... elems) {
	elems_.reserve(sizeof...(elems));
	(elems_.emplace_back(elems.clone()), ...);
}

} // namespace valgo
