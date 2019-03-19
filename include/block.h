#pragma once

#include "color.h"
#include "slide_element.h"

#include <vector>

namespace valgo {

class Block : public SlideElement {
private:
	std::string title_;
	Color color_;
	std::vector<std::unique_ptr<SlideElement>> elems_;

public:
	Block(const Block& be);
	Block& operator=(const Block& be);

	Block(Block&&) noexcept = default;
	Block& operator=(Block&&) noexcept = default;

	explicit Block(std::string title, Color color = Color::BLUE) noexcept;

	template<class... Elem>
	explicit Block(std::string title, Color color, const SlideElement& first_elem,
		const Elem&... elems);

	template<class... Elem>
	explicit Block(std::string title, const SlideElement& first_elem, const Elem&... elems);

	std::unique_ptr<SlideElement> clone() const override;

	// Returns *this to allow chaining
	Block& set_title(std::string title) noexcept;

	// Returns *this to allow chaining
	Block& set_color(Color color) noexcept;

	// Returns *this to allow chaining
	Block& add_elem(const SlideElement& elem);

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

/****************** Implementation ******************/

inline Block::Block(std::string title, Color color) noexcept
	: title_(std::move(title)), color_(color) {}

template<class... Elem>
inline Block::Block(std::string title, const SlideElement& first_elem, const Elem&... elems)
	: Block(std::move(title))
{
	elems_.reserve(1 + sizeof...(elems));
	elems_.emplace_back(first_elem.clone());
	(elems_.emplace_back(elems.clone()), ...);
}

template<class... Elem>
inline Block::Block(std::string title, Color color, const SlideElement& first_elem,
		const Elem&... elems)
	: Block(std::move(title), color)
{
	elems_.reserve(1 + sizeof...(elems));
	elems_.emplace_back(first_elem.clone());
	(elems_.emplace_back(elems.clone()), ...);
}

inline Block& Block::set_title(std::string title) noexcept {
	title_ = std::move(title);
	return *this;
}

inline Block& Block::set_color(Color color) noexcept {
	color_ = color;
	return *this;
}

} // namespace valgo
