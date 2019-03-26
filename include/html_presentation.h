#pragma once

#include "presentation.h"

namespace valgo {

class HTMLPresentation : public Presentation {
	HTMLCode content_;

public:
	HTMLPresentation() = default;

	virtual void add_slide(const Slide& slide) override;

	virtual std::string to_str() const override;
};

} // namespace valgo
