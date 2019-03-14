#include "../include/source_code_element.h"

namespace valgo {
void SourceCodeElement::set_code(std::string source_code) noexcept {
	code_ = std::move(source_code);
}

void SourceCodeElement::set_language(ProgrammingLanguage lang) noexcept {
	lang_ = lang;
}

} // namespace valgo
