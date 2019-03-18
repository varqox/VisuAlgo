#pragma once

#include "slide_element.h"

#include <sstream>
#include <vector>
#include <optional>

#include <iostream>
using namespace std;

namespace valgo {

template <class T>
class Array2D : public SlideElement {
private:
	size_t n_, m_;
	std::string name_;
	bool is_labeled_;
	std::vector<T> vec_; // n_ x m_
	std::vector<std::optional<Color>> colors_; // n_ x m_

	LatexCode draw_labels() const;
	LatexCode draw_cell(size_t row, size_t column) const;
	LatexCode draw_row(size_t row) const;
public:
	Array2D();

	Array2D(std::string name);

	virtual std::unique_ptr<SlideElement> clone() const override;

	Array2D& resize(size_t n, size_t m);

	Array2D& set_elem(size_t i, size_t j, T val);

	Array2D& set_color(size_t i, size_t j, std::optional<Color> color);

	Array2D& set_color_range(size_t a1, size_t a2, size_t b1, size_t b2, std::optional<Color> color);

	Array2D& set_whole_array_color(std::optional<Color>);

	Array2D& set_column_color(size_t column, std::optional<Color> color);

	Array2D& set_row_color(size_t row, std::optional<Color> color);

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

/****************** Implementation ***********************/

	template <class T>
	inline Array2D<T>::Array2D() : is_labeled_(false) {}

	template <class T>
	inline Array2D<T>::Array2D(std::string name) : name_(std::move(name)), is_labeled_(true) {}

	template <class T>
	inline std::unique_ptr<SlideElement> Array2D<T>::clone() const {
		 return std::make_unique<Array2D>(*this);
	}

	template <class T>
	inline Array2D<T>& Array2D<T>::resize(size_t n, size_t m) {
		vec_.resize(n * m);
		colors_.resize(n * m);
		n_ = n;
		m_ = m;
		return *this;
	}

	template <class T>
	inline Array2D<T>& Array2D<T>::set_elem(size_t i, size_t j, T val) {
		vec_[i * m_ + j] = std::move(val);
		return *this;
	}

	template <class T>
	inline Array2D<T>& Array2D<T>::set_color(size_t i, size_t j, std::optional<Color> color) {
		colors_[i * m_ + j] = std::move(color);
		return *this;
	}

	template <class T>
	inline Array2D<T>& Array2D<T>::set_color_range(size_t a1, size_t a2, size_t b1, size_t b2, std::optional<Color> color) {
		if (a1 > b1)
			std::swap(a1, b1);
		if (a2 > b2)
			std::swap(a2, b2);

		for (size_t i = a1; i <= b1; i++)
			for (size_t j = a2; j <= b2; j++)
				set_color(i, j, color);

		return *this;
	}

	template <class T>
	inline Array2D<T>& Array2D<T>::set_whole_array_color(std::optional<Color> color) {
		return set_color_range(0, 0, n_ - 1, m_ - 1, color);
	}

	template <class T>
	inline std::string Array2D<T>::draw_cell(size_t row, size_t column) const {
		std::string cell_color = [&] {
			if (colors_[row * m_ + column].has_value()) {
				switch (colors_[row * m_ + column].value()) {
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
			ret << "\\cellcolor[HTML]{" << cell_color << "}";
		}
		ret << vec_[row * m_ + column] << " ";
		return ret.str();
	}

	template <class T>
	inline Array2D<T>& Array2D<T>::set_row_color(size_t row, std::optional<Color> color) {
		return set_color_range(row, 0, row, m_ - 1, color);
	}

	template <class T>
	inline Array2D<T>& Array2D<T>::set_column_color(size_t column, std::optional<Color> color) {
		return set_color_range(0, column, n_ - 1, column, color);
	}

	template <class T>
	inline LatexCode Array2D<T>::draw_labels() const {
		std::stringstream ret;
		ret << "   \\diag{.1em}{1.1em}{\\footnotesize i}{\\footnotesize j} & ";
		for (size_t j = 0; j < m_; j++) {
			if (j < m_ - 1)
				ret << "\\multicolumn{1}{c}{" << j << "} & ";

			else
				ret << "\\multicolumn{1}{c}{" << j << "}\\\\\n";

		}

		return ret.str();
	}

	template <class T>
	inline std::string Array2D<T>::draw_row(size_t row) const {
		std::stringstream ret;
		ret << "   ";
		for (size_t j = 0; j < m_; j++) {
			ret << draw_cell(row, j);
			if (j < m_ - 1)  {
				ret<< "& ";
			}
			else {
				ret << "\\\\";
			}
		}
		return ret.str();
	}

	template <class T>
	inline LatexCode Array2D<T>::draw_as_latex() const {
		std::stringstream ret;
		ret << "\\begin{table}[h!]\n\\caption{" << name_ <<"[i][j]}\n \\begin{tabular}{";
		if (is_labeled_) ret << "r";
		ret << "|";

		for (size_t i = 0; i < m_; i++) {
			ret << "c|";
		}

		ret << "}\n";

		if (is_labeled_)
			ret << draw_labels();

		auto add_hline = [&] {
			if (is_labeled_)
				ret << "  \\hhline{~|*{" << m_ << "}{-}}\n  ";
			else
				ret << "  \\hline\n";
		};

		add_hline();

		for (size_t i = 0; i < n_; i++) {
			if (is_labeled_) {
				ret << " " << i << " & ";
			}
			ret << draw_row(i) << "\n";

			add_hline();
		}

		ret << " \\end{tabular}\n";
		ret << "\\end{table}\n";

		return ret.str();
	}

	template<class T>
	inline HTMLCode Array2D<T>::draw_as_html() const {
        throw NotImplemented();
    }

} // namespace valgo
