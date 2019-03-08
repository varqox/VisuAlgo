#pragma once

#include <string>

using LatexCode = std::string;
using HTMLCode = std::string;

namespace valgo {

class Drawable {
public:
	Drawable() = default;

	Drawable(const Drawable&) = delete;

	Drawable& operator=(const Drawable&) = delete;

	virtual ~Drawable() = default;

	virtual LatexCode draw_as_latex() const = 0;

	virtual HTMLCode draw_as_html() const = 0;
};

} // namespace valgo
