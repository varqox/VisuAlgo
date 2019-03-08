#pragma once

#include "presentation.h"

namespace valgo {

class HTMLPresentation {
	std::string content_;

public:
	HTMLPresentation() = default;

	virtual void add_slide(const Slide& slide);

	virtual std::string to_str() const;
};

} // namespace valgo
