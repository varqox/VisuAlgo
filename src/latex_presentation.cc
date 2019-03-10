#include "../include/latex_presentation.h"

namespace valgo {

LatexPresentation::LatexPresentation() {
	head_ = "\\documentclass{article}\n\\begin{document}\n";
	tail_ = "\\end{document}";
}

void LatexPresentation::add_slide(const Slide& slide) {
	content_ += "\\newslide\n";
	content_ += slide.draw_as_latex();
}

std::string LatexPresentation::to_str() const {
	std::string ret(head_);
	ret += content_;
	ret += tail_;
	return ret;
}

} // namespace valgo
