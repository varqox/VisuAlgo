#include "../include/latex_presentation.h"
#include "utilities.h"

namespace valgo {

LatexCode LatexPresentation::title() const {
	return title_;
}

void LatexPresentation::title(LatexCode new_title) {
	title_ = std::move(new_title);
}

LatexCode LatexPresentation::footer_title() const {
	return footer_title_;
}

void LatexPresentation::footer_title(LatexCode new_footer_title) {
	footer_title_ = std::move(new_footer_title);
}

std::optional<LatexCode> LatexPresentation::author() const {
	return author_;
}

void LatexPresentation::author(std::optional<LatexCode> new_author) {
	author_ = std::move(new_author);
}

std::optional<LatexCode> LatexPresentation::date() const {
	return date_;
}

void LatexPresentation::date(std::optional<LatexCode> new_date) {
	date_ = std::move(new_date);
}

std::optional<LatexCode> LatexPresentation::institute() const {
	return institute_;
}

void LatexPresentation::institute(std::optional<LatexCode> new_institute) {
	institute_ = std::move(new_institute);
}

void LatexPresentation::add_slide(const Slide& slide) {
	back_insert(content_, '\n', slide.draw_as_latex(), '\n');
}

std::string LatexPresentation::to_str() const {
	std::string ret(concat(
		"\\pdfminorversion=5\n"
		"\\documentclass[table]{beamer}\n"
		"%\n"
		"% Choose how your presentation looks.\n"
		"%\n"
		"% For more themes, color themes and font themes, see:\n"
		"% http://deic.uab.es/~iblanes/beamer_gallery/index_by_theme.html\n"
		"%\n"
		"\\mode<presentation>\n"
		"{\n"
		"  \\usetheme{Madrid}      % or try Darmstadt, Madrid, Warsaw, ...\n"
		"  \\usecolortheme{default} % or try albatross, beaver, crane, ...\n"
		"  \\usefonttheme{default}  % or try serif, structurebold, ...\n"
		"  \\setbeamertemplate{navigation symbols}{}\n"
		"  \\setbeamertemplate{caption}[numbered]\n"
		"}\n"
		"\\usepackage{listings}\n"
		"\\usepackage{textpos}\n"
		"\\usepackage[T1]{fontenc}\n"
		"\\usepackage[polish]{babel}\n"
		"\\usepackage[utf8]{inputenc}\n"
		"\\usepackage{lmodern}\n"
		"\\usepackage{xcolor}\n"
		"\\usepackage{hhline}\n"
		"\\usepackage{graphicx}\n"
		"\\usepackage{fancyvrb}\n"
		"\\selectlanguage{polish}\n"
		"\\usepackage{tikz}"
		"\\newcommand\\diag[4]{%\n"
		"  \\multicolumn{1}{p{#2}}{\\hskip-\\tabcolsep\n"
		"  $\\vcenter{\\begin{tikzpicture}[baseline=0,anchor=south west,inner sep=#1]\n"
		"  \\path[use as bounding box] (0,0) rectangle (#2+2\\tabcolsep,\\baselineskip);\n"
		"  \\node[minimum width={#2+2\\tabcolsep-2\\pgflinewidth},\n"
		"        minimum  height=\\baselineskip+\\extrarowheight+\\pgflinewidth] (box) {};\n"
		"  \\draw[line cap=round] (box.north west) -- (box.south east);\n"
		"  \\node[anchor=south west] at (box.south west) {#3};\n"
		"  \\node[anchor=north east] at (box.north east) {#4};\n"
		" \\end{tikzpicture}}$\\hskip-\\tabcolsep}}\n"
		"\\makeatletter\n"
		"\\newcounter{gr@phviz}\n"
		"\\newenvironment{graphviz}[1]%\n"
		"  {\\refstepcounter{gr@phviz}\n"
		"  \\xdef\\d@tn@me{\\thegr@phviz}%\n"
		"  \\xdef\\r@ncmd{#1 -Tpdf -o \\thegr@phviz.pdf \\thegr@phviz.dot}%\n"
		"  \\typeout{Writing file \\thegr@phviz}\\VerbatimOut{\\thegr@phviz.dot}%\n"
		"  }\n"
		"  {\\endVerbatimOut %\n"
		" \\toks0{\\immediate\\write18}%\n"
		" \\expandafter\\toks\\expandafter1\\expandafter{\\r@ncmd}%\n"
		" \\edef\\d@r@ncmd{\\the\\toks0{\\the\\toks1}}\\d@r@ncmd %\n"
		" \\includegraphics[scale=0.5]{\\d@tn@me.pdf}%\n"
		" \\immediate\\write18{rm \\d@tn@me.dot \\d@tn@me.pdf}%\n"
		"}\n"
		"\\makeatother\n"
		"\\makeatletter\n"
		"\\newenvironment{colorblock}[2]\n"
		"{\n"
		"  \\definecolor{b@secolor}{HTML}{#1}%\n"
		"  \\definecolor{f@ntcolor}{HTML}{#2}%\n"
		"  \\setbeamercolor{upp@r}{fg=f@ntcolor,bg=b@secolor}%\n"
		"  \\setbeamercolor{l@wer}{fg=black,bg=b@secolor!20!white}%\n"
		"  \\setbeamercolor{item}{fg=upp@r,bg=upp@r}%\n"
		"  \\begin{beamerboxesrounded}[upper=upp@r,lower=l@wer,shadow=true]}\n"
		"{\n"
		"  \\end{beamerboxesrounded}\n"
		"}\n"
		"\\makeatother\n"
		"\n"
		"\\title[", title_, "]{", footer_title_, "}\n"));

	if (author_.has_value())
		back_insert(ret, "\\author{", author_.value(), "}\n");

	if (institute_.has_value())
		back_insert(ret, "\\institute{", institute_.value(), "}\n");

	if (date_.has_value())
		back_insert(ret, "\\date{", date_.value(), "}\n");

	back_insert(ret, "\n"
		"\\begin{document}\n"
		"\n"
		"\\begin{frame}\n"
		"  \\titlepage\n"
		"\\end{frame}\n",
		content_,
		"\\end{document}\n");

	return ret;
}

} // namespace valgo
