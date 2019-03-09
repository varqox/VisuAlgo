#pragma once

#include "slide_view.h"

namespace valgo {

class Presentation {
public:
	Presentation() = default;

	virtual ~Presentation() = default;

	virtual void add_slide(const SlideView& slide_view) = 0;

	virtual std::string to_str() const = 0;
};

} // namespace valgo
