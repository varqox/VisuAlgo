#include "../include/itemize.h"
#include "utilities.h"

namespace valgo {

Itemize::Itemize(const Itemize& be) {
	elems_.reserve(be.elems_.size());
	for (auto const& elem : be.elems_)
		elems_.emplace_back(elem->clone());
}

Itemize& Itemize::operator=(const Itemize& elem) { return (*this = Itemize(elem)); }

std::unique_ptr<SlideElement> Itemize::clone() const { return std::make_unique<Itemize>(*this); }

Itemize& Itemize::add_item(const SlideElement& elem) {
	elems_.emplace_back(elem.clone());
	return *this;
}

LatexCode Itemize::draw_as_latex() const {
	auto res = concat("\\begin{itemize}\n");
	for (auto const& elem : elems_)
		back_insert(res, "\\item ", elem->draw_as_latex(), '\n');

	return back_insert(res, "\\end{itemize}");
}

HTMLCode Itemize::draw_as_html() const { throw NotImplemented(); }

} // namespace valgo
