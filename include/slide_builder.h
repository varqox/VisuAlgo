#pragma once

#include "slide.h"

namespace valgo {

class SlideBuilder {
private:
	std::vector<SlideElement*> elems_;

public:
	SlideBuilder() = default;

	void add_elem(SlideElement& elem);

	void remove_elem(SlideElement& elem);

	void remove_all_elements();

	Slide build() const;
};

} // namespace valgo
