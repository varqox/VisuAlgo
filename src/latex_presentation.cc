#include "../include/latex_presentation.h"
#include "utilities.h"

namespace valgo {

LatexCode LatexPresentation::language() const { return language_; }

void LatexPresentation::language(LatexCode new_language) { language_ = std::move(new_language); }

LatexCode LatexPresentation::title() const { return title_; }

void LatexPresentation::title(LatexCode new_title) { title_ = std::move(new_title); }

LatexCode LatexPresentation::footer_title() const { return footer_title_; }

void LatexPresentation::footer_title(LatexCode new_footer_title) { footer_title_ = std::move(new_footer_title); }

std::optional<LatexCode> LatexPresentation::author() const { return author_; }

void LatexPresentation::author(std::optional<LatexCode> new_author) { author_ = std::move(new_author); }

std::optional<LatexCode> LatexPresentation::footer_author() const { return footer_author_; }

void LatexPresentation::footer_author(std::optional<LatexCode> new_footer_author) {
	footer_author_ = std::move(new_footer_author);
}

std::optional<LatexCode> LatexPresentation::date() const { return date_; }

void LatexPresentation::date(std::optional<LatexCode> new_date) { date_ = std::move(new_date); }

std::optional<LatexCode> LatexPresentation::footer_date() const { return footer_date_; }

void LatexPresentation::footer_date(std::optional<LatexCode> new_footer_date) {
	footer_date_ = std::move(new_footer_date);
}

std::optional<LatexCode> LatexPresentation::institute() const { return institute_; }

void LatexPresentation::institute(std::optional<LatexCode> new_institute) { institute_ = std::move(new_institute); }

std::optional<LatexCode> LatexPresentation::footer_institute() const { return footer_institute_; }

void LatexPresentation::footer_institute(std::optional<LatexCode> new_footer_institute) {
	footer_institute_ = std::move(new_footer_institute);
}

void LatexPresentation::add_slide(const Slide& slide) { back_insert(content_, "%\n", slide.draw_as_latex(), '\n'); }

void LatexPresentation::add_section(const LatexCode& section_name) {
	back_insert(content_, "%\n\\section{", section_name, "}\n");
}

void LatexPresentation::add_subsection(const LatexCode& subsection_name) {
	back_insert(content_, "%\n\\subsection{", subsection_name, "}\n");
}

std::string LatexPresentation::to_str() const {
	std::string ret(concat("\\pdfminorversion=5\n"
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
	                       "\\usepackage{caption}\n"
	                       "\\usepackage[T1]{fontenc}\n"
	                       "\\usepackage[",
	                       language_,
	                       "]{babel}\n"
	                       "\\usepackage[utf8]{inputenc}\n"
	                       "\\usepackage{lmodern}\n"
	                       "\\usepackage{xcolor}\n"
	                       "\\usepackage{hhline}\n"
	                       "\\usepackage{graphicx}\n"
	                       "\\usepackage{fancyvrb}\n"
	                       "\\selectlanguage{",
	                       language_,
	                       "}\n"
	                       "\\usepackage{tikz}"
	                       "\\usepackage{tkz-euclide}"
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
	                       "\\title[",
	                       footer_title_, "]{", title_, "}\n"));

	if (author_.has_value() or footer_author_.has_value()) {
		back_insert(ret, "\\author");
		if (footer_author_.has_value())
			back_insert(ret, '[', footer_author_.value(), ']');
		back_insert(ret, "{", author_.value_or(""), "}\n");
	}

	if (institute_.has_value() or footer_institute_.has_value()) {
		back_insert(ret, "\\institute");
		if (footer_institute_.has_value())
			back_insert(ret, '[', footer_institute_.value(), ']');
		back_insert(ret, "{", institute_.value_or(""), "}\n");
	}

	if (date_.has_value() or footer_date_.has_value()) {
		back_insert(ret, "\\date");
		if (footer_date_.has_value())
			back_insert(ret, '[', footer_date_.value(), ']');
		back_insert(ret, "{", date_.value_or(""), "}\n");
	}

	back_insert(ret,
	            "\n"
	            "\\begin{document}\n"
	            "\n"
	            "\\begin{frame}\n"
	            "  \\titlepage\n"
	            "\\end{frame}\n",
	            content_, "\\end{document}\n");

	return ret;
}

} // namespace valgo
