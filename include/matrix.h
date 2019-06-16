#pragma once

#include "slide_element.h"

#include <vector>
#include <sstream>

namespace valgo {

template<class T>
class Matrix : public SlideElement {
private:
	int rows_, columns_;
	std::vector <std::vector<T>> matrix_;

public:
	Matrix();

	Matrix(int rows, int columns);

	Matrix &set_rows(int rows);

	Matrix &set_columns(int columns);

	Matrix &set_elem(int row, int column, T value);

	virtual std::unique_ptr <SlideElement> clone() const override;

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

/****************** Implementation ***********************/

template<class T>
inline Matrix<T>::Matrix() {}

template<class T>
inline Matrix<T>::Matrix(int rows, int columns) : rows_(rows), columns_(columns) {
	matrix_.resize(rows_, std::vector<T>(columns_));
}

template<class T>
inline Matrix<T> &Matrix<T>::set_rows(int rows) {
	rows_ = rows;
	matrix_.resize(rows_, std::vector<T>(columns_));
	return *this;
}

template<class T>
inline Matrix<T> &Matrix<T>::set_columns(int columns) {
	columns_ = columns;
	for (std::vector<T> &row : matrix_) {
		row.resize(columns_);
	}
	return *this;
}

template<class T>
inline Matrix<T> &Matrix<T>::set_elem(int row, int column, T value) {
	matrix_[row][column] = std::move(value);
	return *this;
}

template<class T>
inline std::unique_ptr <SlideElement> Matrix<T>::clone() const {
	return std::make_unique<Matrix>(*this);
}

template<class T>
inline LatexCode Matrix<T>::draw_as_latex() const {
	std::stringstream res;
	res << "$\\begin{bmatrix}" << std::endl;
	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < columns_; ++j) {
			if (j)
				res << "& ";
			res << matrix_[i][j] << " ";
		}

		if (i + 1 != rows_)
			res << " \\\\";
		res << std::endl;
	}
	res << "\\end{bmatrix}$" << std::endl;

	return res.str();
}

template<class T>
inline HTMLCode Matrix<T>::draw_as_html() const {
	throw NotImplemented();
}

} // namespace valgo