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

	std::string title() const { return title_; }

	void title(std::string new_title) { title_ = std::move(new_title); }

	std::string footer_title() const { return footer_title_; }

	void footer_title(std::string new_footer_title) {
		footer_title_ = std::move(new_footer_title);
	}

	std::optional<std::string> author() const { return author_; }

	void author(std::optional<std::string> new_author) {
		author_ = std::move(new_author);
	}

	std::optional<std::string> date() const { return date_; }

	void date(std::optional<std::string> new_date) {
		date_ = std::move(new_date);
	}

	std::optional<std::string> institute() const { return institute_; }

	void institute(std::optional<std::string> new_institute) {
		institute_ = std::move(new_institute);
	}

	virtual void add_slide(const Slide& slide) override;

	virtual std::string to_str() const override;
};

} // namespace valgo
