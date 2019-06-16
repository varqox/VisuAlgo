#pragma once

#include "color.h"
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
	size_t rows_, columns_;
	std::optional<LatexCode> name_;
	std::vector<std::pair<T, std::optional<Color>>> elems_; // rows_ x columns_

	LatexCode draw_labels() const;
	LatexCode draw_cell(size_t row, size_t column) const;
	LatexCode draw_row(size_t row) const;

public:
	Array2D(size_t rows, size_t columns);

	Array2D(LatexCode name, size_t rows, size_t columns);

	virtual std::unique_ptr<SlideElement> clone() const override;

	Array2D& resize(size_t rows, size_t columns);

	Array2D& set_elem(size_t row, size_t column, T val);

	Array2D& set_elem(size_t row, size_t column, T&& val, std::optional<Color> color);

	Array2D& set_color(size_t row, size_t column, std::optional<Color> color);

	Array2D& set_color_range(size_t first_row, size_t last_row, size_t first_column, size_t last_column, std::optional<Color> color);

	Array2D& set_whole_array_color(std::optional<Color>);

	Array2D& set_column_color(size_t column, std::optional<Color> color);

	Array2D& set_row_color(size_t row, std::optional<Color> color);

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

/****************** Implementation ***********************/

template <class T>
inline LatexCode Array2D<T>::draw_labels() const {
	std::stringstream ret;
	ret << "   \\diag{.1em}{1.1em}{\\footnotesize i}{\\footnotesize j} & ";
	for (size_t column = 0; column < columns_; ++column) {
		if (column < columns_ - 1)
			ret << "\\multicolumn{1}{c}{" << column << "} & ";
		else
			ret << "\\multicolumn{1}{c}{" << column << "}\\\\\n";
	}

	return ret.str();
}

template <class T>
inline std::string Array2D<T>::draw_row(size_t row) const {
	std::stringstream ret;
	ret << "   ";
	for (size_t column = 0; column < columns_; ++column) {
		ret << draw_cell(row, column);
		if (column < columns_ - 1)
			ret << "& ";
		else
			ret << "\\\\";
	}
	return ret.str();
}

template <class T>
inline Array2D<T>::Array2D(size_t rows, size_t columns)
	: rows_(rows), columns_(columns), elems_(rows * columns) {}

template <class T>
inline Array2D<T>::Array2D(LatexCode name, size_t rows, size_t columns)
	: rows_(rows), columns_(columns), name_(std::move(name)), elems_(rows * columns) {}

template <class T>
inline std::unique_ptr<SlideElement> Array2D<T>::clone() const {
	 return std::make_unique<Array2D>(*this);
}

template <class T>
inline Array2D<T>& Array2D<T>::resize(size_t rows, size_t columns) {
	decltype(elems_) new_elems(rows * columns); // OK if throws
	for (size_t r = 0; r < std::min(rows_, rows); ++r)
		for (size_t c = 0; c < std::min(columns_, columns); ++c)
			new_elems[r * columns + c] = elems_[r * columns_ + c]; // OK if throws

	elems_ = std::move(new_elems); // OK if throws
	rows_ = rows;
	columns_ = columns;
	return *this;
}

template <class T>
inline Array2D<T>& Array2D<T>::set_elem(size_t row, size_t column, T val) {
	elems_[row * columns_ + column].first = std::move(val);
	return *this;
}

template <class T>
inline Array2D<T>& Array2D<T>::set_elem(size_t row, size_t column, T&& val, std::optional<Color> color) {
	set_elem(row, column, std::forward<T>(val));
	set_color(row, column, std::move(color));
	return *this;
}

template <class T>
inline Array2D<T>& Array2D<T>::set_color(size_t row, size_t column, std::optional<Color> color) {
	elems_[row * columns_ + column].second = std::move(color);
	return *this;
}

template <class T>
inline Array2D<T>& Array2D<T>::set_color_range(size_t first_row, size_t last_row, size_t first_column, size_t last_column, std::optional<Color> color) {
	for (size_t row = first_row; row <= last_row; ++row)
		for (size_t column = first_column; column <= last_column; ++column)
			set_color(row, column, color);

	return *this;
}

template <class T>
inline Array2D<T>& Array2D<T>::set_whole_array_color(std::optional<Color> color) {
	return set_color_range(0, rows_ - 1, 0, columns_ - 1, color);
}

template <class T>
inline std::string Array2D<T>::draw_cell(size_t row, size_t column) const {
	std::stringstream ret;
	if (elems_[row * columns_ + column].second.has_value()) {
		ret << "\\cellcolor[HTML]{" << elems_[row * columns_ + column].second.value().to_hex() << "}";
	}

	ret << elems_[row * columns_ + column].first << " ";
	return ret.str();
}

template <class T>
inline Array2D<T>& Array2D<T>::set_row_color(size_t row, std::optional<Color> color) {
	return set_color_range(row, row, 0, columns_ - 1, color);
}

template <class T>
inline Array2D<T>& Array2D<T>::set_column_color(size_t column, std::optional<Color> color) {
	return set_color_range(0, rows_ - 1, column, column, color);
}

template <class T>
inline LatexCode Array2D<T>::draw_as_latex() const {
	std::stringstream ret;
	ret << "\\begin{table}[h!]\n"
		"\\captionsetup{labelsep=none}\n"
		"\\renewcommand{\\thetable}{}\n"
		"\\caption{" << name_.value_or("") <<"}\n"
		"\\begin{tabular}{";
	if (name_.has_value())
		ret << "r";
	ret << "|";

	for (size_t row = 0; row < columns_; ++row)
		ret << "c|";

	ret << "}\n";

	if (name_.has_value())
		ret << draw_labels();

	auto add_hline = [&] {
		if (name_.has_value())
			ret << "  \\hhline{~|*{" << columns_ << "}{-}}\n  ";
		else
			ret << "  \\hline\n";
	};

	add_hline();

	for (size_t row = 0; row < rows_; ++row) {
		if (name_.has_value())
			ret << " " << row << " & ";
		ret << draw_row(row) << "\n";

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
