#include "../include/slide.h"

namespace valgo {

void Slide::add_element(SlideElement* elem) {
	elems_.push_back(elem->clone());
}

LatexCode Slide::draw_as_latex() const {
	LatexCode ret;
	for (auto& elem : elems_) {
		ret += elem.get()->draw_as_latex();
		ret += "\\\\\n";
	}
	return ret;
}

HTMLCode Slide::draw_as_html() const {
	LatexCode ret;
	for (auto& elem : elems_) {
		ret += elem.get()->draw_as_latex();
		ret += "\\\\\n";
	}
	return ret;
}

} // namespace valgo