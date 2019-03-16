#include "../include/source_code.h"
#include "utilities.h"

namespace valgo {

std::unique_ptr<SlideElement> SourceCode::clone() const {
	return std::make_unique<SourceCode>(*this);
}

SourceCode& SourceCode::set_title(std::optional<std::string> title) {
	title_ = std::move(title);
	return *this;
}

SourceCode& SourceCode::set_code(std::string source_code) noexcept {
	code_ = std::move(source_code);
	return *this;
}

SourceCode& SourceCode::set_lang(std::string lang) noexcept {
	lang_ = std::move(lang);
	return *this;
}

LatexCode SourceCode::draw_as_latex() const {
	return concat("\\begin{lstlisting}[",
		"language=", lang_, ",",
		title_.has_value() ? concat("title=", title_.value(), ',') : "",
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

HTMLCode SourceCode::draw_as_html() const {
	throw NotImplemented();
}

} // namespace valgo
