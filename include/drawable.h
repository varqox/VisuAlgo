#pragma once

#include <stdexcept>
#include <string>

namespace valgo {

using LatexCode = std::string;
using HTMLCode = std::string;

class NotImplemented : public std::logic_error {
public:
	NotImplemented() : std::logic_error("Function not yet implemented") {}
};

class Drawable {
public:
	Drawable() = default;

	virtual ~Drawable() = default;

	virtual LatexCode draw_as_latex() const = 0;

	virtual HTMLCode draw_as_html() const = 0;
};

} // namespace valgo
