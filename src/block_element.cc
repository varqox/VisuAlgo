#include "../include/block_element.h"
#include "utilities.h"

namespace valgo {

BlockElement::BlockElement(const BlockElement& be) : title_(be.title_), color_(be.color_) {
	elems_.reserve(be.elems_.size());
	for (auto const& elem : be.elems_)
		elems_.emplace_back(elem->clone());
}

BlockElement& BlockElement::operator=(const BlockElement& elem) {
	return (*this = BlockElement(elem));
}

std::unique_ptr<SlideElement> BlockElement::clone() const {
	return std::make_unique<BlockElement>(*this);
}

BlockElement& BlockElement::add_element(const SlideElement& elem) {
	elems_.emplace_back(elem.clone());
	return *this;
}

LatexCode BlockElement::draw_as_latex() const {
	auto block_name = [&]{
		switch (color_) {
		case BLUE: return "block";
		case RED: return "alertblock";
		}
	}();

	auto res = concat("\\begin{", block_name, "}{", title_, "}\n");
	for (auto const& elem : elems_)
		back_insert(res, elem->draw_as_latex(), '\n');

	return back_insert(res, "\\end{", block_name, "}");
}

HTMLCode BlockElement::draw_as_html() const {
	throw NotImplemented();
}

} // namespace valgo
