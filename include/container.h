#pragma once

#include "color.h"
#include "slide_element.h"

#include <array>
#include <deque>
#include <map>
#include <set>
#include <sstream>
#include <vector>

namespace valgo {

template<class T>
class Container : public SlideElement {
public:
	Container(const T&);

	virtual std::unique_ptr<SlideElement> clone() const override;

	virtual LatexCode draw_as_latex() const override;

	virtual HTMLCode draw_as_html() const override;
};

class ContainerImplDetails {
private:
	template<class T>
	friend class Container;

	// prints elements [beg, end) with corresponding colors [color_beg, color_end) - *(beg + i) with color
	// *(color_beg + i)
	template<class Iter, class ColorIter>
	static LatexCode draw_as_latex(Iter beg, Iter end, ColorIter color_beg, ColorIter color_end) {
		std::stringstream res;
		res << "\\begin{equation*}\n[";

		for (auto i = beg; i != end; ++i) {
			if (i != beg)
				res << ',';
			if (color_beg != color_end) {
				if (color_beg->has_value())
					res << "\\textcolor[HTML]{" << color_beg->value().to_hex() << "}{" << *i << "}";
				else
					res << *i;

				++color_beg;

			} else {
				res << *i;
			}
		}

		res << "]\n\\end{equation*}\n";
		return res.str();
	}

	// prints elements [beg, end) with corresponding colors: *(beg + i) with color colors[color_beg + i]
	template<class Iter>
	static LatexCode draw_as_latex(
		const char* beg_str, const char* end_str, Iter beg, Iter end,
		const std::map<const typename std::iterator_traits<Iter>::value_type*, std::optional<Color>>& colors)
	{
		std::stringstream res;
		res << "\\begin{equation*}\n" << beg_str;

		for (auto i = beg; i != end; ++i) {
			if (i != beg)
				res << ',';

			auto it = colors.find(&*i);
			if (it != colors.end())
				res << "\\textcolor[HTML]{" << it->second.value().to_hex() << "}{" << *i << "}";
			else
				res << *i;
		}

		res << end_str << "\n\\end{equation*}\n";
		return res.str();
	}
};

template<class T, size_t N>
class Container<std::array<T, N>> : public SlideElement {
private:
	const std::array<T, N>* arr_;
	std::array<std::optional<Color>, N> colors_ = {{}};

public:
	Container(const std::array<T, N>& arr) : arr_(std::addressof(arr)) {}

	virtual std::unique_ptr<SlideElement> clone() const override { return std::make_unique<Container>(*this); }

	Container& set_color(size_t n, std::optional<Color> color) {
		colors_[n] = std::move(color);
		return *this;
	}

	// Sets color of elements in range [beg, end)
	Container& set_range_color(size_t beg, size_t end, std::optional<Color> color) {
		std::fill(colors_.begin() + beg, colors_.begin() + end, std::move(color));
		return *this;
	}

	// Sets color of every element
	Container& set_whole_color(std::optional<Color> color) {
		std::fill(colors_.begin(), colors_.end(), std::move(color));
		return *this;
	}

	virtual LatexCode draw_as_latex() const override {
		return ContainerImplDetails::draw_as_latex(arr_->begin(), arr_->end(), colors_.begin(), colors_.end());
	}

	virtual HTMLCode draw_as_html() const override { throw NotImplemented(); }
};

template<class T>
class Container<std::vector<T>> : public SlideElement {
private:
	const std::vector<T>* vec_;
	std::vector<std::optional<Color>> colors_;

public:
	Container(const std::vector<T>& vec) : vec_(std::addressof(vec)) {}

	virtual std::unique_ptr<SlideElement> clone() const override { return std::make_unique<Container>(*this); }

	Container& set_color(size_t n, std::optional<Color> color) {
		colors_.resize(vec_->size());
		colors_[n] = std::move(color);
		return *this;
	}

	// Sets color of elements in range [beg, end)
	Container& set_range_color(size_t beg, size_t end, std::optional<Color> color) {
		colors_.resize(vec_->size());
		std::fill(colors_.begin() + beg, colors_.begin() + end, std::move(color));
		return *this;
	}

	// Sets color of every element
	Container& set_whole_color(std::optional<Color> color) {
		colors_.assign(vec_->size(), std::move(color));
		return *this;
	}

	virtual LatexCode draw_as_latex() const override {
		return ContainerImplDetails::draw_as_latex(vec_->begin(), vec_->end(), colors_.begin(), colors_.end());
	}

	virtual HTMLCode draw_as_html() const override { throw NotImplemented(); }
};

template<class T>
class Container<std::set<T>> : public SlideElement {
private:
	const std::set<T>* set_;
	std::map<const T*, std::optional<Color>> colors_;

public:
	Container(const std::set<T>& set) : set_(std::addressof(set)) {}

	Container(Container&& cont) = default;
	Container(const Container& cont) = default;
	Container& operator=(Container&& cont) = default;
	Container& operator=(const Container& cont) = default;

	virtual std::unique_ptr<SlideElement> clone() const override { return std::make_unique<Container>(*this); }

	Container& set_color(typename std::set<T>::const_iterator it, std::optional<Color> color) {
		if (color.has_value())
			colors_[&*it] = std::move(color);
		else
			colors_.erase(&*it);

		return *this;
	}

	Container& set_color(const T& elem, std::optional<Color> color) {
		auto it = set_->find(elem);
		if (it != set_->end())
			set_color(std::move(it), std::move(color));

		return *this;
	}

	// Sets color of elements in range [beg, end)
	Container& set_range_color(typename std::set<T>::const_iterator beg, typename std::set<T>::const_iterator end,
	                           std::optional<Color> color) {
		while (beg != end)
			set_color(beg++, color);

		return *this;
	}

	// Sets color of every element
	Container& set_whole_color(std::optional<Color> color) {
		if (color.has_value())
			return set_range_color(set_->begin(), set_->end(), std::move(color));

		colors_.clear();
		return *this;
	}

	virtual LatexCode draw_as_latex() const override {
		return ContainerImplDetails::draw_as_latex("\\{", "\\}", set_->begin(), set_->end(), colors_);
	}

	virtual HTMLCode draw_as_html() const override { throw NotImplemented(); }
};

template<class T>
class Container<std::multiset<T>> : public SlideElement {
private:
	const std::multiset<T>* mset_;
	std::map<const T*, std::optional<Color>> colors_;

public:
	Container(const std::multiset<T>& mset) : mset_(std::addressof(mset)) {}

	Container(Container&& cont) = default;
	Container(const Container& cont) = default;
	Container& operator=(Container&& cont) = default;
	Container& operator=(const Container& cont) = default;

	virtual std::unique_ptr<SlideElement> clone() const override { return std::make_unique<Container>(*this); }

	Container& set_color(typename std::multiset<T>::const_iterator it, std::optional<Color> color) {
		if (color.has_value())
			colors_[&*it] = std::move(color);
		else
			colors_.erase(&*it);

		return *this;
	}

	// Sets color of elements in range [beg, end)
	Container& set_range_color(typename std::multiset<T>::const_iterator beg,
	                           typename std::multiset<T>::const_iterator end, std::optional<Color> color) {
		while (beg != end)
			set_color(beg++, color);

		return *this;
	}

	Container& set_color(const T& elem, std::optional<Color> color) {
		return set_range_color(mset_->lower_bound(elem), mset_->upper_bound(elem), std::move(color));
	}

	// Sets color of every element
	Container& set_whole_color(std::optional<Color> color) {
		if (color.has_value())
			return set_range_color(mset_->begin(), mset_->end(), std::move(color));

		colors_.clear();
		return *this;
	}

	virtual LatexCode draw_as_latex() const override {
		return ContainerImplDetails::draw_as_latex("\\{", "\\}", mset_->begin(), mset_->end(), colors_);
	}

	virtual HTMLCode draw_as_html() const override { throw NotImplemented(); }
};

} // namespace valgo
