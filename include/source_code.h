#pragma once

#include "slide_element.h"

#include <optional>
#include <vector>

namespace valgo {

class SourceCode : public SlideElement {
private:
	std::optional<LatexCode> title_;
	std::string lang_;
	std::string code_;

public:
	SourceCode() = default;

	virtual std::unique_ptr<SlideElement> clone() const override;

	SourceCode& set_title(std::optional<LatexCode> title);

	// Returns *this to allow chaining
	SourceCode& set_code(std::string source_code) noexcept;

	// Sets programming language to @p lang. @p lang should be a valid
	// lstlisting LaTeX package language e.g. "C", "C++", "Python", ...
	// Returns *this to allow chaining
	SourceCode& set_lang(std::string lang) noexcept;

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

} // namespace valgo
