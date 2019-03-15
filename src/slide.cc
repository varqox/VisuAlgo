#include "../include/slide.h"
#include "utilities.h"

namespace valgo {

void Slide::add_element(const SlideElement& elem) {
	elems_.emplace_back(elem.clone());
}

LatexCode Slide::draw_as_latex() const {
	LatexCode ret("\\begin{frame}[fragile");

	if (allow_multi_slide_)
		back_insert(ret, ",allowframebreaks");
	if (shrink_)
		back_insert(ret, ",shrink");

	back_insert(ret, "]{", title_, "}\n");

	for (auto& elem : elems_)
		back_insert(ret, elem.get()->draw_as_latex(), '\n');

	return back_insert(ret, "\\end{frame}");
}

HTMLCode Slide::draw_as_html() const {
	throw NotImplemented();
}

} // namespace valgo
