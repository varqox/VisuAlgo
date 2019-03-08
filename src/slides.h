#pragma once

#include "drawable.h"

#include <memory>
#include <vector>

namespace valgo {

class Slide {
private:
	SlideContent content;
	std::vector<Drawable*> elements;
public:
	Slide() = default;
	void add_element(Drawable& elem);
	void remove_element(Drawable& elem);
	void remove_all_elements();
	SlideContent build();
};

} // namespace valgo
