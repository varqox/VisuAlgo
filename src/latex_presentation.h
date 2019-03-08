#pragma once

#include "presentation.h"

namespace valgo {

class LatexPresentation {
	std::string content_;

public:
	LatexPresentation() = default;

	virtual void add_slide(const Slide& slide);

	virtual std::string to_str() const;
};

} // namespace valgo
