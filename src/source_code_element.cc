#include "../include/source_code_element.h"
#include "utilities.h"

namespace valgo {

std::unique_ptr<SlideElement> SourceCodeElement::clone() const {
	return std::make_unique<SourceCodeElement>(*this);
}

SourceCodeElement& SourceCodeElement::set_code(std::string source_code) noexcept {
	code_ = std::move(source_code);
	return *this;
}

SourceCodeElement& SourceCodeElement::set_lang(std::string lang) noexcept {
	lang_ = std::move(lang);
	return *this;
}

LatexCode SourceCodeElement::draw_as_latex() const {
	return concat("\\begin{lstlisting}[",
		"language=", lang_, ","
		"numbers=left,"
		"xleftmargin=16pt,"
		"basicstyle=\\small\\ttfamily,"
		"showstringspaces=false,"
		"numbersep=6pt,"
		"numberstyle=\\small\\ttfamily,"
		"columns=spaceflexible,"
		"keepspaces=true,"
		"tabsize=4,"
		"breaklines=true,"
		"commentstyle=\\color{gray},"
		"keywordstyle=\\color{blue}\\bfseries,"
		"stringstyle=\\color{purple}]\n",
		code_,
		"\\end{lstlisting}");
}

HTMLCode SourceCodeElement::draw_as_html() const {
	throw NotImplemented();
}

} // namespace valgo
