#pragma once

#include "presentation.h"

#include <optional>

namespace valgo {

class LatexPresentation : public Presentation {
	std::string content_;
	std::string title_, footer_title_;
	std::optional<std::string> author_, date_, institute_;

public:
	LatexPresentation(std::string title, std::string footer_title) noexcept
		: title_(std::move(title)), footer_title_(std::move(footer_title)) {}

	std::string title() const;

	void title(std::string new_title);

	std::string footer_title() const;

	void footer_title(std::string new_footer_title);

	std::optional<std::string> author() const;

	void author(std::optional<std::string> new_author);

	std::optional<std::string> date() const;

	void date(std::optional<std::string> new_date);

	std::optional<std::string> institute() const;

	void institute(std::optional<std::string> new_institute);

	virtual void add_slide(const Slide& slide) override;

	virtual std::string to_str() const override;
};

} // namespace valgo
