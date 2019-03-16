#pragma once

#include "slide_element.h"

#include <vector>

namespace valgo {

class ItemizeElement : public SlideElement {
private:
	std::vector<std::unique_ptr<SlideElement>> elems_;

public:
	ItemizeElement(const ItemizeElement& be);
	ItemizeElement& operator=(const ItemizeElement& be);

	ItemizeElement(ItemizeElement&&) noexcept = default;
	ItemizeElement& operator=(ItemizeElement&&) noexcept = default;

	ItemizeElement() noexcept = default;

	template<class... Elem>
	explicit ItemizeElement(const Elem&... elems);

	std::unique_ptr<SlideElement> clone() const override;

	// Returns *this to allow chaining
	ItemizeElement& add_item(const SlideElement& elem);

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

/****************** Implementation ******************/

template<class... Elem>
inline ItemizeElement::ItemizeElement(const Elem&... elems) {
	elems_.reserve(sizeof...(elems));
	(elems_.emplace_back(elems.clone()), ...);
}

} // namespace valgo
