#pragma once

#include "presentation.h"

namespace valgo {

class HTMLPresentation : public Presentation {
	std::string content_;

public:
	HTMLPresentation() = default;

	virtual void add_slide(const SlideView& slide_view) override;

	virtual std::string to_str() const override;
};

} // namespace valgo
