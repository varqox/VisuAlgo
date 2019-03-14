#pragma once

#include "slide_element.h"

#include <vector>

namespace valgo {

class SourceCodeElement : public SlideElement {
private:
	std::string lang_;
	std::string code_;

public:
	SourceCodeElement() = default;

	virtual std::unique_ptr<SlideElement> clone() const override;

	// Returns *this to allow chaining
	SourceCodeElement& set_code(std::string source_code) noexcept;

	// Sets programming language to @p lang. @p lang should be a valid
	// lstlisting LaTeX package language e.g. "C", "C++", "Python", ...
	// Returns *this to allow chaining
	SourceCodeElement& set_lang(std::string lang) noexcept;

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

} // namespace valgo
