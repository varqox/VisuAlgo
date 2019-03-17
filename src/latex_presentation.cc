#include "../include/latex_presentation.h"
#include "utilities.h"

namespace valgo {

std::string LatexPresentation::title() const {
	return title_;
}

void LatexPresentation::title(std::string new_title) {
	title_ = std::move(new_title);
}

std::string LatexPresentation::footer_title() const {
	return footer_title_;
}

void LatexPresentation::footer_title(std::string new_footer_title) {
	footer_title_ = std::move(new_footer_title);
}

std::optional<std::string> LatexPresentation::author() const {
	return author_;
}

void LatexPresentation::author(std::optional<std::string> new_author) {
	author_ = std::move(new_author);
}

std::optional<std::string> LatexPresentation::date() const {
	return date_;
}

void LatexPresentation::date(std::optional<std::string> new_date) {
	date_ = std::move(new_date);
}

std::optional<std::string> LatexPresentation::institute() const {
	return institute_;
}

void LatexPresentation::institute(std::optional<std::string> new_institute) {
	institute_ = std::move(new_institute);
}

void LatexPresentation::add_slide(const Slide& slide) {
	back_insert(content_, '\n', slide.draw_as_latex(), '\n');
}

std::string LatexPresentation::to_str() const {
	std::string ret(concat("\\documentclass[table]{beamer}\n"
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
		"\\selectlanguage{polish}\n"
		"\\definecolor{colbrown}{RGB}{124,71,50}\n"
		"\\newenvironment<>{block_brown}[1]\n"
		"{\n"
		"  \\setbeamercolor{block title}{fg=white, bg=colbrown}%\n"
		"  \\setbeamercolor{block body}{fg=black, bg=colbrown!20!white}%\n"
		"  \\begin{actionenv}#2%\n"
		"  \\def\\insertblocktitle{#1}%\n"
		"  \\par%\n"
		"  \\usebeamertemplate{block begin}%\n"
		"}\n"
		"{\n"
		"  \\par%\n"
		"  \\usebeamertemplate{block end}%\n"
		"  \\setbeamercolor{block title}{use=structure, fg=white, bg=structure.fg!75!black}%\n"
		"  \\setbeamercolor{block body}{parent=normal text,use=block title,bg=block title.bg!10!bg}%\n"
		"  \\end{actionenv}%\n"
		"}\n"
		"\\definecolor{colyellow}{rgb}{1.0, 1.0, 0.0}\n"
		"\\newenvironment<>{block_yellow}[1]\n"
		"{\n"
		"  \\setbeamercolor{block title}{fg=black, bg=colyellow}%\n"
		"  \\setbeamercolor{block body}{fg=black, bg=colyellow!20!white}%\n"
		"  \\begin{actionenv}#2%\n"
		"  \\def\\insertblocktitle{#1}%\n"
		"  \\par%\n"
		"  \\usebeamertemplate{block begin}%\n"
		"}\n"
		"{\n"
		"  \\par%\n"
		"  \\usebeamertemplate{block end}%\n"
		"  \\setbeamercolor{block title}{use=structure, fg=white,bg=structure.fg!75!black}%\n"
		"  \\setbeamercolor{block body}{parent=normal text, use=block title, bg=block title.bg!10!bg}%\n"
		"  \\end{actionenv}%\n"
		"}\n"
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
