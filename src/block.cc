#include "../include/block.h"
#include "utilities.h"

namespace valgo {

Block::Block(const Block& be) : title_(be.title_), color_(be.color_) {
	elems_.reserve(be.elems_.size());
	for (auto const& elem : be.elems_)
		elems_.emplace_back(elem->clone());
}

Block& Block::operator=(const Block& elem) {
	return (*this = Block(elem));
}

std::unique_ptr<SlideElement> Block::clone() const {
	return std::make_unique<Block>(*this);
}

Block& Block::add_elem(const SlideElement& elem) {
	elems_.emplace_back(elem.clone());
	return *this;
}

LatexCode Block::draw_as_latex() const {
	auto res = concat("\\begin{colorblock}{", color_.to_hex(), "}{",
		contrast_color(color_).to_hex(), "}{", title_, "}\n");
	for (auto const& elem : elems_)
		back_insert(res, elem->draw_as_latex(), '\n');
	return back_insert(res, "\\end{colorblock}");
}

HTMLCode Block::draw_as_html() const {
	throw NotImplemented();
}

} // namespace valgo
