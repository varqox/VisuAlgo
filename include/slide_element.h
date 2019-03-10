#pragma once

#include "drawable.h"

#include <memory>

namespace valgo {

class SlideElement : public Drawable {
public:
	SlideElement() = default;

	virtual std::unique_ptr<SlideElement> clone() const = 0;
};

} // namespace valgo
