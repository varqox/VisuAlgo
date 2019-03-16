#pragma once

#include "slide_element.h"

#include <memory>
#include <vector>

namespace valgo {

class Slide : public Drawable {
private:
	std::vector<std::unique_ptr<SlideElement>> elems_;
	std::string title_; // Empty title means no title
	bool allow_multi_slide_ = false;
	bool shrink_ = false;

public:
	Slide() = default;

	template<class... Elem>
	explicit Slide(const Elem&... elems);

	Slide& set_title(std::string title) noexcept;

	// Sets whether it is allowed to put overflowing contents on many slides.
	// Returns *this to allow chaining
	Slide& allow_multi_silde(bool val) noexcept;

	// Sets whether the contents should be shrank to fit on one slide.
	// Returns *this to allow chaining
	Slide& shrink(bool val) noexcept;

	// Returns *this to allow chaining
	Slide& add_elem(const SlideElement& elem);

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

/****************** Implementation ******************/

template<class... Elem>
inline Slide::Slide(const Elem&... elems) {
	elems_.reserve(sizeof...(elems));
	(elems_.emplace_back(elems.clone()), ...);
}

inline Slide& Slide::set_title(std::string title) noexcept {
	title_ = std::move(title);
	return *this;
}

inline Slide& Slide::allow_multi_silde(bool val) noexcept {
	allow_multi_slide_ = val;
	return *this;
}

inline Slide& Slide::shrink(bool val) noexcept {
	shrink_ = val;
	return *this;
}

} // namespace valgo
