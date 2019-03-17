#pragma once

#include "slide_element.h"

#include <optional>
#include <sstream>
#include <vector>

namespace valgo {

template<class T>
class Array1D : public SlideElement {
private:
	std::vector<T> vec_;
	std::string name_;
	bool is_labeled_;
	std::vector<std::optional<Color>> colors_;

	std::string draw_bottom_labels() const;
	std::string draw_cells() const;
	std::string draw_cell(size_t cell_number) const;

public:
	Array1D();

	Array1D(std::string name);

	virtual std::unique_ptr<SlideElement> clone() const override;

	Array1D& set(std::vector<T> vec) noexcept;

	Array1D& resize(size_t n);

	Array1D& set_elem(size_t n, T val);

	Array1D& set_color(size_t n, std::optional<Color> color);

	Array1D& set_range_color(size_t a, size_t b, std::optional<Color> color);

	Array1D& set_whole_array_color(std::optional<Color> color);

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

/****************** Implementation ***********************/

template <class T>
inline Array1D<T>& Array1D<T>::set_color(size_t n, std::optional<Color> color) {
	colors_[n] = std::move(color);
	return *this;
}

template <class T>
inline Array1D<T>& Array1D<T>::set_range_color(size_t a, size_t b, std::optional<Color> color) {
	if (a > b)
		std::swap(a, b);
	for (size_t i = a; i <= b; i++)
		set_color(i, color);
	return *this;
}

template <class T>
inline Array1D<T>& Array1D<T>::set_whole_array_color(std::optional<Color> color) {
	for (size_t i = 0; i < colors_.size(); i++)
		set_color(i, color);
	return *this;
}

template <class T>
inline std::string Array1D<T>::draw_cell(size_t cell_number) const {
	std::string cell_color = [&] {
		if (colors_[cell_number].has_value()) {
			switch (colors_[cell_number].value()) {
				case Color::BLUE: return "AFEEEE";
				case Color::RED: return "FF6961";
				case Color::GREEN: return "C0D890";
				case Color::BROWN: return "96735A";
				case Color::YELLOW: return "FFFF80";
			}
		}
		return ""; // std::nullopt
	}();

	std::stringstream ret;
	if (!cell_color.empty()) {
		ret << "\\cellcolor[HTML]{" << cell_color << "} ";
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
inline Array1D<T>& Array1D<T>::set(std::vector<T> vec) noexcept {
	vec_ = std::move(vec);
	colors_ = std::move(std::vector<std::optional<Color>>(vec_.size(), std::nullopt));
	return *this;
}

template <class T>
inline Array1D<T>& Array1D<T>::resize(size_t n) {
	vec_.resize(n);
	return *this;
}

template <class T>
inline Array1D<T>& Array1D<T>::set_elem(size_t n, T val) {
	vec_[n] = std::move(val);
	return *this;
}

template <class T>
inline std::string Array1D<T>::draw_cells() const {
	std::stringstream ret;
	for (size_t i = 0; i < vec_.size(); i++) {
		ret << draw_cell(i);
		if (i < vec_.size() - 1)  {
			ret<< "& ";
		}
		else {
			ret << "\\\\\n";
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
			ret << "  \\hhline{~|*{" << vec_.size() << "}{-}}\n  ";
		else
			ret << "  \\hline\n";
	};

	add_hline();

	if (is_labeled_) {
		ret << name_ << "[i] &";
	}
	ret <<"   " << draw_cells();

	add_hline();

	if (is_labeled_) {
		ret << draw_bottom_labels();
	}

	ret << " \\end{tabular}\n";
	ret << "\\end{table}\n";

	return ret.str();
}

template <class T>
inline HTMLCode Array1D<T>::draw_as_html() const {
	throw NotImplemented();
}

} // namespace valgo
