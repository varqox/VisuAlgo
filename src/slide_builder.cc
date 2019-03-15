#include "../include/slide_builder.h"

#include <algorithm>

namespace valgo {

void SlideBuilder::add_element(SlideElement& elem) {
	elems_.emplace_back(&elem);
}

void SlideBuilder::remove_element(SlideElement& elem) {
	elems_.erase(std::find(elems_.begin(), elems_.end(), &elem));
}

void SlideBuilder::remove_all_elements() {
	elems_.clear();
}

Slide SlideBuilder::build() const {
	Slide ret;
	for (SlideElement* elem : elems_)
		ret.add_element(*elem);
	return ret;
}

} // namespace valgo
