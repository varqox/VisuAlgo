#pragma once

#include "slide_element.h"

#include <sstream>
#include <vector>

namespace valgo {

template<class T>
class Array1D : public SlideElement {
public:
	enum Color {BLUE, RED, GREEN, NONE};

private:
	std::vector<T> vec_;
	std::string name_;
	bool is_labeled_;
	std::vector<Color> colors_;

	std::string draw_bottom_labels() const;
	std::string draw_cells() const;
	std::string draw_cell(size_t cell_number) const;

public:
	Array1D();

	Array1D(std::string name);

	virtual std::unique_ptr<SlideElement> clone() const override;

	void set(std::vector<T> vec) noexcept;

	void resize(size_t n);

	void set_elem(size_t n, T val);

	void set_color(size_t n, Color);

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

/****************** Implementation ***********************/

template <class T>
inline void Array1D<T>::set_color(size_t n, Color color) {
	colors_[n] = std::move(color);
}

template <class T>
inline std::string Array1D<T>::draw_cell(size_t cell_number) const {
	std::string cell_color = [&]{
		switch (colors_[cell_number]) {
			case BLUE: return "AFEEEE";
			case RED: return "FF6961";
			case GREEN: return "C0D890";
			case NONE: return "";
		}
	}();

	std::stringstream ret;
	if (!cell_color.empty()) {
		ret << "\\cellcolor[HTML]{" << cell_color << "}";
	}
	ret << vec_[cell_number] << " ";
	return ret.str();
}

template <class T>
inline std::string Array1D<T>::draw_bottom_labels() const {
	std::stringstream ret;
	ret << "\\multicolumn{1}{c}{i} & ";
	for (size_t i = 0; i < vec_.size(); i++) {
		if (i < vec_.size() - 1)  {
			ret << "\\multicolumn{1}{c}{" << i << "} & ";
		}
		else {
			ret << "\\multicolumn{1}{c}{" << i << "} ";
		}
	}
	return ret.str();
}

template <class T>
inline Array1D<T>::Array1D() : is_labeled_(false) {}

template <class T>
inline Array1D<T>::Array1D(std::string name) : name_(std::move(name)), is_labeled_(true)  {}

template <class T>
inline std::unique_ptr<SlideElement> Array1D<T>::clone() const {
	return std::make_unique<Array1D>(*this);
}

template <class T>
inline void Array1D<T>::set(std::vector<T> vec) noexcept {
	vec_ = std::move(vec);
	colors_ = std::move(std::vector<Color>(vec_.size(), NONE));
}

template <class T>
inline void Array1D<T>::resize(size_t n) {
	vec_.resize(n);
}

template <class T>
inline void Array1D<T>::set_elem(size_t n, T val) {
	vec_[n] = std::move(val);
}

template <class T>
inline std::string Array1D<T>::draw_cells() const {
	std::stringstream ret;
	for (size_t i = 0; i < vec_.size(); i++) {
		ret << draw_cell(i);
		if (i < vec_.size() - 1)  {
			ret<< " &";
		}
		else {
			ret << "\n";
		}
	}
	return ret.str();
}

template <class T>
inline LatexCode Array1D<T>::draw_as_latex() const {
	std::stringstream ret;
	ret << "\\begin{table}[h!]\n \\begin{tabular}{";
	if (is_labeled_) ret << "c";
	ret << "|";

	for (size_t i = 0; i < vec_.size(); i++) {
		ret << "c|";
	}

	ret << "}\n";

	auto add_hline = [&] {
		if (is_labeled_)
			ret << " \\hhline{~|*{" << vec_.size() << "}{-}}\n  ";
		else
			ret << " \\hline";
	};

	add_hline();

	if (is_labeled_) {
		ret << name_ << "[i] &";
	}
	ret << draw_cells();

	ret << "\\\\ ";
	add_hline();

	if (is_labeled_) {
		ret << draw_bottom_labels();
	}

	ret << " \n \\end{tabular} \n";
	ret << "  \\end{table}\n";

	return ret.str();
}

template <class T>
inline HTMLCode Array1D<T>::draw_as_html() const {
	throw NotImplemented();
}

} // namespace valgo
