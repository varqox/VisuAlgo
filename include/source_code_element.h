#pragma once

#include "slide_element.h"

#include <vector>

namespace valgo {

enum class ProgrammingLanguage {
	ASSEMBLER,
	AWK,
	BASH,
	C,
	CAML,
	CPP,
	GO,
	HASKELL,
	HTML,
	JAVA,
	LATEX,
	LLVM,
	MAKE,
	MATHEMATICA,
	MATLAB,
	PASCAL,
	PERL,
	PYTHON,
	R,
	RUBY,
	SCALA,
	SH,
	SQL,
	TEX,
	XML,
};

class SourceCodeElement : public SlideElement {
private:

	ProgrammingLanguage lang_;
	std::string code_;

public:
	SourceCodeElement() = default;

	virtual std::unique_ptr<SlideElement> clone() const override;

	void set_code(std::string source_code) noexcept;

	void set_language(ProgrammingLanguage lang) noexcept;

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

} // namespace valgo
