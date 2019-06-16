#pragma once

#include "color.h"
#include "slide_element.h"

#include <optional>
#include <sstream>
#include <vector>

namespace valgo {

template<class T>
class Array1D : public SlideElement {
private:
	std::optional<LatexCode> name_;
	std::vector<std::pair<T, std::optional<Color>>> elems_;

	void copy_vec_to_elems(const std::vector<T>& vec);

	LatexCode draw_bottom_labels() const;

	LatexCode draw_cells() const;

	LatexCode draw_cell(size_t cell_number) const;

public:
	explicit Array1D(const std::vector<T>& vec);

	explicit Array1D(size_t size);

	Array1D(LatexCode name, const std::vector<T>& vec);

	Array1D(LatexCode name, size_t size);

	Array1D& operator=(const std::vector<T>& vec);

	virtual std::unique_ptr<SlideElement> clone() const override;

	Array1D& resize(size_t size);

	Array1D& set_elem(size_t idx, T val);

	Array1D& set_elem(size_t idx, T&& val, std::optional<Color> color);

	Array1D& set_elem(size_t idx, T val, std::optional<Color> color);

	Array1D& set_color(size_t idx, std::optional<Color> color);

	Array1D& set_range_color(size_t first, size_t last, std::optional<Color> color);

	Array1D& set_whole_array_color(std::optional<Color> color);

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

/****************** Implementation ***********************/

template<class T>
inline void Array1D<T>::copy_vec_to_elems(const std::vector<T>& vec) {
	elems_.resize(vec.size());
	for (size_t i = 0; i < vec.size(); ++i) {
		elems_[i].first = vec[i];
		elems_[i].second = std::nullopt;
	}
}

template <class T>
inline std::string Array1D<T>::draw_bottom_labels() const {
	std::stringstream ret;
	ret << " \\multicolumn{1}{c}{i} & ";
	for (size_t i = 0; i < elems_.size(); ++i) {
		if (i < elems_.size() - 1)
			ret << "\\multicolumn{1}{c}{" << i << "} & ";
		else
			ret << "\\multicolumn{1}{c}{" << i << "} \n";
	}
	return ret.str();
}

template <class T>
inline std::string Array1D<T>::draw_cells() const {
	std::stringstream ret;
	for (size_t i = 0; i < elems_.size(); ++i) {
		ret << draw_cell(i);
		if (i < elems_.size() - 1)
			ret << "& ";
		else
			ret << "\\\\\n";
	}
	return ret.str();
}

template <class T>
inline std::string Array1D<T>::draw_cell(size_t cell_idx) const {
	std::stringstream ret;
	if (elems_[cell_idx].second.has_value()) {
		ret << "\\cellcolor[HTML]{" << elems_[cell_idx].second.value().to_hex() << "}";
	}
	ret << elems_[cell_idx].first << " ";
	return ret.str();
}

template <class T>
inline Array1D<T>::Array1D(const std::vector<T>& vec) : elems_(vec.size()) { copy_vec_to_elems(vec); }

template <class T>
inline Array1D<T>::Array1D(size_t size) : elems_(size) {}

template <class T>
inline Array1D<T>::Array1D(LatexCode name, const std::vector<T>& vec) : name_(std::move(name)), elems_(vec.size()) {
	copy_vec_to_elems(vec);
}

template <class T>
inline Array1D<T>::Array1D(LatexCode name, size_t size) : name_(std::move(name)), elems_(size) {}

template <class T>
inline Array1D<T>& Array1D<T>::operator=(const std::vector<T>& vec) {
	copy_vec_to_elems(vec);
	return *this;
}

template <class T>
inline std::unique_ptr<SlideElement> Array1D<T>::clone() const {
	return std::make_unique<Array1D>(*this);
}

template <class T>
inline Array1D<T>& Array1D<T>::resize(size_t size) {
	elems_.resize(size);
	return *this;
}

template <class T>
inline Array1D<T>& Array1D<T>::set_elem(size_t idx, T val) {
	elems_[idx].first = std::move(val);
	return *this;
}

template <class T>
inline Array1D<T>& Array1D<T>::set_elem(size_t idx, T&& val, std::optional<Color> color) {
	set_elem(idx, std::forward<T>(val));
	set_color(idx, std::move(color));
	return *this;
}

template <class T>
inline Array1D<T>& Array1D<T>::set_color(size_t idx, std::optional<Color> color) {
	elems_[idx].second = std::move(color);
	return *this;
}

template <class T>
inline Array1D<T>& Array1D<T>::set_range_color(size_t first, size_t last, std::optional<Color> color) {
	for (size_t i = first; i <= last; ++i)
		set_color(i, color);
	return *this;
}

template <class T>
inline Array1D<T>& Array1D<T>::set_whole_array_color(std::optional<Color> color) {
	for (size_t i = 0; i < elems_.size(); ++i)
		set_color(i, color);
	return *this;
}

template <class T>
inline LatexCode Array1D<T>::draw_as_latex() const {
	std::stringstream ret;
	ret << "\\begin{table}[h!]\n \\begin{tabular}{";
	if (name_.has_value())
		ret << "c";
	ret << "|";

	for (size_t i = 0; i < elems_.size(); ++i)
		ret << "c|";

	ret << "}\n";

	auto add_hline = [&] {
		if (name_.has_value())
			ret << "  \\hhline{~|*{" << elems_.size() << "}{-}}\n  ";
		else
			ret << "  \\hline\n";
	};

	add_hline();

	if (name_.has_value())
		ret << " " << name_.value() << "[i] & ";
	ret << draw_cells();

	add_hline();

	if (name_.has_value())
		ret << draw_bottom_labels();

	ret << " \\end{tabular}\n";
	ret << "\\end{table}\n";

	return ret.str();
}

template <class T>
inline HTMLCode Array1D<T>::draw_as_html() const {
	throw NotImplemented();
}

} // namespace valgo
