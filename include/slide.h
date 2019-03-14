#pragma once

#include "slide_element.h"

#include <memory>
#include <vector>

namespace valgo {

class Slide : public Drawable {
private:
	std::vector<std::unique_ptr<SlideElement>> elems_;
	bool allow_multi_slide_ = true;
	bool shrink_ = false;

public:
	template<class... Elem>
	explicit Slide(const Elem&... elems);

	// Sets whether it is allowed to put overflowing contents on many slides.
	// Returns *this to allow chaining
	Slide& allow_multi_silde(bool val) noexcept {
		allow_multi_slide_ = val;
		return *this;
	}

	// Sets whether the contents should be shrank to fit on one slide.
	// Returns *this to allow chaining
	Slide& shrink(bool val) noexcept {
		shrink_ = val;
		return *this;
	}

	void add_element(const SlideElement* elem);

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

/****************** Implementation ******************/

template<class... Elem>
inline Slide::Slide(const Elem&... elems) {
	elems_.reserve(sizeof...(elems));
	(elems_.emplace_back(elems.clone()), ...);
}

} // namespace valgo
