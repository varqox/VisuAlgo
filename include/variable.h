#pragma once

#include "slide_element.h"

#include <sstream>
#include <vector>

namespace valgo {

template<class T>
class Variable : public SlideElement {
private:
	const LatexCode name_;
	T var_;

public:
	Variable(LatexCode name);

	virtual std::unique_ptr<SlideElement> clone() const override;

	void set(T var);

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

/****************** Implementation ******************/

template<class T>
inline Variable<T>::Variable(LatexCode name) : name_(std::move(name)) {}

template<class T>
inline void Variable<T>::set(T var) {
	var_ = std::move(var);
}

template <class T>
inline LatexCode Variable<T>::draw_as_latex() const {
	std::stringstream latex_code;
	latex_code << name_ << " = " << var_;
	return latex_code.str();
}

template<class T>
inline std::unique_ptr<SlideElement> Variable<T>::clone() const {
	return std::make_unique<Variable>(*this);
}

template<class T>
inline HTMLCode Variable<T>::draw_as_html() const {
	throw NotImplemented();
}

} // namespace valgo
