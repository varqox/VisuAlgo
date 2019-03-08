#pragma once

#include <string>

namespace valgo {

class SlideContent {
private:
	std::string source;
public:
	explicit SlideContent(const std::string& source);
	explicit SlideContent(const char* source);
	
	void setSource(const std::string& source);
	void setSource(const char* source);
	std::string getSource() const;
};

} // namespace valgo
