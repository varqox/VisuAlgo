#pragma once

#include "slide_element.h"

#include <vector>

namespace valgo {

class BlockElement : public SlideElement {
public:
	enum Color { BLUE, RED };

private:
	std::string title_;
	Color color_;
	std::vector<std::unique_ptr<SlideElement>> elems_;

public:
	BlockElement(const BlockElement& be);
	BlockElement& operator=(const BlockElement& be);

	BlockElement(BlockElement&&) noexcept = default;
	BlockElement& operator=(BlockElement&&) noexcept = default;

	explicit BlockElement(std::string title, Color color = BLUE) noexcept;

	template<class... Elem>
	explicit BlockElement(std::string title, Color color, const SlideElement& first_elem,
		const Elem&... elems);

	template<class... Elem>
	explicit BlockElement(std::string title, const SlideElement& first_elem, const Elem&... elems);

	std::unique_ptr<SlideElement> clone() const override;

	// Returns *this to allow chaining
	BlockElement& set_title(std::string title) noexcept;

	// Returns *this to allow chaining
	BlockElement& set_color(Color color) noexcept;

	// Returns *this to allow chaining
	BlockElement& add_element(const SlideElement& elem);

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

/****************** Implementation ******************/

inline BlockElement::BlockElement(std::string title, Color color) noexcept
	: title_(std::move(title)), color_(color) {}

template<class... Elem>
inline BlockElement::BlockElement(std::string title, const SlideElement& first_elem, const Elem&... elems)
	: BlockElement(std::move(title))
{
	elems_.reserve(1 + sizeof...(elems));
	elems_.emplace_back(first_elem.clone());
	(elems_.emplace_back(elems.clone()), ...);
}

template<class... Elem>
inline BlockElement::BlockElement(std::string title, Color color, const SlideElement& first_elem,
		const Elem&... elems)
	: BlockElement(std::move(title), color)
{
	elems_.reserve(1 + sizeof...(elems));
	elems_.emplace_back(first_elem.clone());
	(elems_.emplace_back(elems.clone()), ...);
}

inline BlockElement& BlockElement::set_title(std::string title) noexcept {
	title_ = std::move(title);
	return *this;
}

inline BlockElement& BlockElement::set_color(Color color) noexcept {
	color_ = color;
	return *this;
}

} // namespace valgo
