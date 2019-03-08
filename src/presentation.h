#pragma once

#include "slide.h"

namespace valgo {

class Presentation {
public:
	Presentation() = default;

	virtual ~Presentation() = default;

	virtual void add_slide(const Slide& slide) = 0;

	virtual std::string to_str() const = 0;
};

} // namespace valgo
