#pragma once

#include "slide_element.h"

#include <vector>

namespace valgo {

template<class T>
class Variable : public SlideElement {
private:
	const std::string name_;
	T var_;

public:
	Variable(std::string name);

	virtual std::unique_ptr<SlideElement> clone() const override;

	void set(T var) { var_ = std::move(var); }

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

/****************** Implementation ******************/

template<class T>
inline Variable<T>::Variable(std::string name) : name_(std::move(name)) {}

} // namespace valgo
