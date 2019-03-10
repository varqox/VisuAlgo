#pragma once

#include "presentation.h"

namespace valgo {

class LatexPresentation : public Presentation {
	std::string content_;

public:
	LatexPresentation() = default;

	virtual void add_slide(const Slide& slide) override;

	virtual std::string to_str() const override;
};

} // namespace valgo
