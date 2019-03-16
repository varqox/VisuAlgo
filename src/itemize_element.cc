#include "../include/itemize_element.h"
#include "utilities.h"

namespace valgo {

ItemizeElement::ItemizeElement(const ItemizeElement& be) {
	elems_.reserve(be.elems_.size());
	for (auto const& elem : be.elems_)
		elems_.emplace_back(elem->clone());
}

ItemizeElement& ItemizeElement::operator=(const ItemizeElement& elem) {
	return (*this = ItemizeElement(elem));
}

std::unique_ptr<SlideElement> ItemizeElement::clone() const {
	return std::make_unique<ItemizeElement>(*this);
}

ItemizeElement& ItemizeElement::add_item(const SlideElement& elem) {
	elems_.emplace_back(elem.clone());
	return *this;
}

LatexCode ItemizeElement::draw_as_latex() const {
	auto res = concat("\\begin{itemize}\n");
	for (auto const& elem : elems_)
		back_insert(res, "\\item ", elem->draw_as_latex(), '\n');

	return back_insert(res, "\\end{itemize}");
}

HTMLCode ItemizeElement::draw_as_html() const {
	throw NotImplemented();
}

} // namespace valgo
