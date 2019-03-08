#pragma once

#include "slide_content.h"

namespace valgo {

class Drawable {
public:
	Drawable() = default;
	virtual ~Drawable() = default;
	Drawable(const Drawable&) = delete;
	Drawable& operator=(const Drawable&) = delete;
	
	virtual SlideContent draw() const = 0;
};

} // namespace valgo
