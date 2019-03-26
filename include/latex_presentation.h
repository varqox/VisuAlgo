#pragma once

#include "presentation.h"

#include <optional>

namespace valgo {

class LatexPresentation : public Presentation {
	LatexCode content_;
	LatexCode title_, footer_title_;
	std::optional<LatexCode> author_, date_, institute_;

public:
	LatexPresentation(LatexCode title, LatexCode footer_title) noexcept
		: title_(std::move(title)), footer_title_(std::move(footer_title)) {}

	LatexCode title() const;

	void title(LatexCode new_title);

	LatexCode footer_title() const;

	void footer_title(LatexCode new_footer_title);

	std::optional<LatexCode> author() const;

	void author(std::optional<LatexCode> new_author);

	std::optional<LatexCode> date() const;

	void date(std::optional<LatexCode> new_date);

	std::optional<LatexCode> institute() const;

	void institute(std::optional<LatexCode> new_institute);

	virtual void add_slide(const Slide& slide) override;

	virtual std::string to_str() const override;
};

} // namespace valgo
