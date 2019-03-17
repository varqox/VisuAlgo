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
	auto block_name = [&]{
		switch (color_) {
		case Color::BLUE: return "block";
		case Color::RED: return "alertblock";
		case Color::GREEN: return "exampleblock";
		case Color::BROWN: return "block_brown";
		case Color::YELLOW: return "block_yellow";
		}
	}();

	auto res = concat("\\begin{", block_name, "}{", title_, "}\n");
	for (auto const& elem : elems_)
		back_insert(res, elem->draw_as_latex(), '\n');

	return back_insert(res, "\\end{", block_name, "}");
}

HTMLCode Block::draw_as_html() const {
	throw NotImplemented();
}

} // namespace valgo
