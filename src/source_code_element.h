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

class SourceCodeElement : public Drawable {
private:

	ProgrammingLanguage lang_;
	std::string code_;

public:
	SourceCodeElement() = default;

	void set_code(std::string source_code) noexcept {
		code_ = std::move(source_code);
	}

	void set_language(ProgrammingLanguage lang) noexcept { lang_ = lang; }

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

} // namespace valgo
