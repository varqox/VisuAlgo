#pragma once

#include "../drawable.h"

#include <string>

namespace valgo {

class Latex : public Drawable {
private:
	SlideContent source;
public:
	explicit Latex(const std::string& source);
	explicit Latex(const char* source);
	
	SlideContent draw() const;
	
	void setLatex(const std::string& source);
	void setLatex(const char* source);
};

} // namespace valgo
