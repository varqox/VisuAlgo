#pragma once

#include "color.h"
#include "slide_element.h"

#include <array>
#include <deque>
#include <forward_list>
#include <functional>
#include <list>
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
	static LatexCode draw_as_latex(
		Iter beg, Iter end, ColorIter color_beg, ColorIter color_end,
		const std::function<void(std::stringstream&, const typename
			std::iterator_traits<Iter>::value_type&)>& printer =
			[](auto& ss, auto&& val) { ss << val; }) {
		std::stringstream res;
		res << "\\begin{equation*}\n[";

		for (auto i = beg; i != end; ++i) {
			if (i != beg)
				res << ',';
			if (color_beg != color_end) {
				if (color_beg->has_value()) {
					res << "\\textcolor[HTML]{" << color_beg->value().to_hex() << "}{";
					printer(res, *i);
					res << "}";
				} else {
					printer(res, *i);
				}

				++color_beg;

			} else {
				printer(res, *i);
			}
		}

		res << "]\n\\end{equation*}\n";
		return res.str();
	}

	// prints elements [beg, end) with corresponding colors: *(beg + i) with color colors[key_of(*(beg + i))]
	template<class Iter, class Key, class KeyOf, class Printer>
	static LatexCode draw_as_latex(
		const char* beg_str, const char* end_str, Iter beg, Iter end,
		const std::map<const Key*, std::optional<Color>>& colors, KeyOf&& key_of, Printer&& printer) {
		static_assert(std::is_invocable_r_v<const Key*, KeyOf, Iter>);
		static_assert(std::is_invocable_r_v<void, Printer, std::stringstream&,
			const typename std::iterator_traits<Iter>::value_type&>);

		std::stringstream res;
		res << "\\begin{equation*}\n" << beg_str;

		for (auto i = beg; i != end; ++i) {
			if (i != beg)
				res << ',';

			auto it = colors.find(key_of(i));
			if (it != colors.end()) {
				res << "\\textcolor[HTML]{" << it->second.value().to_hex() << "}{";
				printer(res, *i);
				res << "}";
			} else {
				printer(res, *i);
			}
		}

		res << end_str << "\n\\end{equation*}\n";
		return res.str();
	}


	// prints elements [beg, end) with corresponding colors: *(beg + i) with color colors[key_of(*(beg + i))]
	template<class Iter, class Key>
	static LatexCode draw_as_latex(
		const char* beg_str, const char* end_str, Iter beg, Iter end,
		const std::map<const Key*, std::optional<Color>>& colors) {
		return draw_as_latex(beg_str, end_str, beg, end, colors, [](auto&& iter) { return &*iter; },
			[](auto& ss, auto&& val) { ss << val; });
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
class Container<std::deque<T>> : public SlideElement {
private:
	const std::deque<T>* deq_;
	std::vector<std::optional<Color>> colors_;

public:
	Container(const std::deque<T>& deq) : deq_(std::addressof(deq)) {}

	virtual std::unique_ptr<SlideElement> clone() const override { return std::make_unique<Container>(*this); }

	Container& set_color(size_t n, std::optional<Color> color) {
		colors_.resize(deq_->size());
		colors_[n] = std::move(color);
		return *this;
	}

	// Sets color of elements in range [beg, end)
	Container& set_range_color(size_t beg, size_t end, std::optional<Color> color) {
		colors_.resize(deq_->size());
		std::fill(colors_.begin() + beg, colors_.begin() + end, std::move(color));
		return *this;
	}

	// Sets color of every element
	Container& set_whole_color(std::optional<Color> color) {
		colors_.assign(deq_->size(), std::move(color));
		return *this;
	}

	virtual LatexCode draw_as_latex() const override {
		return ContainerImplDetails::draw_as_latex(deq_->begin(), deq_->end(), colors_.begin(), colors_.end());
	}

	virtual HTMLCode draw_as_html() const override { throw NotImplemented(); }
};

template<class T>
class Container<std::list<T>> : public SlideElement {
private:
	const std::list<T>* list_;
	std::map<const T*, std::optional<Color>> colors_;

public:
	Container(const std::list<T>& list) : list_(std::addressof(list)) {}

	virtual std::unique_ptr<SlideElement> clone() const override { return std::make_unique<Container>(*this); }

	Container& set_color(typename std::list<T>::const_iterator it, std::optional<Color> color) {
		if (color.has_value())
			colors_[&*it] = std::move(color);
		else
			colors_.erase(&*it);

		return *this;
	}

	Container& set_color(size_t n, std::optional<Color> color) {
		if (n < list_->size()) {
			auto it = list_->begin();
			std::advance(it, n);
			set_color(it, std::move(color));
		}

		return *this;
	}

	// Sets color of elements in range [beg, end)
	Container& set_range_color(typename std::list<T>::const_iterator beg, typename std::list<T>::const_iterator end,
	                           std::optional<Color> color) {
		while (beg != end)
			set_color(beg++, color);

		return *this;
	}

	// Sets color of elements in range [beg, end)
	Container& set_range_color(size_t beg, size_t end, std::optional<Color> color) {
		auto it = list_->begin();
		advance(it, beg);
		auto it2 = it;
		advance(it2, end - beg);
		set_range_color(it, it2, std::move(color));
		return *this;
	}

	// Sets color of every element
	Container& set_whole_color(std::optional<Color> color) {
		if (color.has_value())
			return set_range_color(list_->begin(), list_->end(), std::move(color));

		colors_.clear();
		return *this;
	}

	virtual LatexCode draw_as_latex() const override {
		return ContainerImplDetails::draw_as_latex("[", "]", list_->begin(), list_->end(), colors_);
	}

	virtual HTMLCode draw_as_html() const override { throw NotImplemented(); }
};

template<class T>
class Container<std::forward_list<T>> : public SlideElement {
private:
	const std::forward_list<T>* list_;
	std::map<const T*, std::optional<Color>> colors_;

public:
	Container(const std::forward_list<T>& list) : list_(std::addressof(list)) {}

	virtual std::unique_ptr<SlideElement> clone() const override { return std::make_unique<Container>(*this); }

	Container& set_color(typename std::forward_list<T>::const_iterator it, std::optional<Color> color) {
		if (color.has_value())
			colors_[&*it] = std::move(color);
		else
			colors_.erase(&*it);

		return *this;
	}

	Container& set_color(size_t n, std::optional<Color> color) {
		auto it = list_->begin();
		// advance(it, n) but check for end()
		while (n-- > 0 && it != list_->end())
			++it;

		if (it != list_->end())
			set_color(it, std::move(color));

		return *this;
	}

	// Sets color of elements in range [beg, end)
	Container& set_range_color(typename std::forward_list<T>::const_iterator beg, typename std::forward_list<T>::const_iterator end,
	                           std::optional<Color> color) {
		while (beg != end)
			set_color(beg++, color);

		return *this;
	}

	// Sets color of elements in range [beg, end)
	Container& set_range_color(size_t beg, size_t end, std::optional<Color> color) {
		auto it = list_->begin();
		advance(it, beg);
		auto it2 = it;
		advance(it2, end - beg);
		set_range_color(it, it2, std::move(color));
		return *this;
	}

	// Sets color of every element
	Container& set_whole_color(std::optional<Color> color) {
		if (color.has_value())
			return set_range_color(list_->begin(), list_->end(), std::move(color));

		colors_.clear();
		return *this;
	}

	virtual LatexCode draw_as_latex() const override {
		return ContainerImplDetails::draw_as_latex("[", "]", list_->begin(), list_->end(), colors_);
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

template<class K, class V>
class Container<std::map<K, V>> : public SlideElement {
private:
	const std::map<K, V>* map_;
	std::map<const K*, std::optional<Color>> colors_;

public:
	Container(const std::map<K, V>& map) : map_(std::addressof(map)) {}

	virtual std::unique_ptr<SlideElement> clone() const override { return std::make_unique<Container>(*this); }

	Container& set_color(typename std::map<K, V>::const_iterator it, std::optional<Color> color) {
		if (color.has_value())
			colors_[&it->first] = std::move(color);
		else
			colors_.erase(&it->first);

		return *this;
	}

	Container& set_color(const K& key, std::optional<Color> color) {
		auto it = map_->find(key);
		if (it != map_->end())
			set_color(std::move(it), std::move(color));

		return *this;
	}

	// Sets color of elements in range [beg, end)
	Container& set_range_color(typename std::map<K, V>::const_iterator beg, typename std::map<K, V>::const_iterator end,
	                           std::optional<Color> color) {
		while (beg != end)
			set_color(beg++, color);

		return *this;
	}

	// Sets color of every element
	Container& set_whole_color(std::optional<Color> color) {
		if (color.has_value())
			return set_range_color(map_->begin(), map_->end(), std::move(color));

		colors_.clear();
		return *this;
	}

	virtual LatexCode draw_as_latex() const override {
		return ContainerImplDetails::draw_as_latex("\\{", "\\}", map_->begin(), map_->end(), colors_,
			[](auto&& iter) { return &iter->first; },
			[](auto& ss, auto&& pk) {
				ss << pk.first << " \\mapsto " << pk.second;
			});
	}

	virtual HTMLCode draw_as_html() const override { throw NotImplemented(); }
};

template<class K, class V>
class Container<std::multimap<K, V>> : public SlideElement {
private:
	const std::multimap<K, V>* mmap_;
	std::map<const K*, std::optional<Color>> colors_;

public:
	Container(const std::multimap<K, V>& mmap) : mmap_(std::addressof(mmap)) {}

	virtual std::unique_ptr<SlideElement> clone() const override { return std::make_unique<Container>(*this); }

	Container& set_color(typename std::multimap<K, V>::const_iterator it, std::optional<Color> color) {
		if (color.has_value())
			colors_[&it->first] = std::move(color);
		else
			colors_.erase(&it->first);

		return *this;
	}

	// Sets color of elements in range [beg, end)
	Container& set_range_color(typename std::multimap<K, V>::const_iterator beg,
	                           typename std::multimap<K, V>::const_iterator end, std::optional<Color> color) {
		while (beg != end)
			set_color(beg++, color);

		return *this;
	}

	Container& set_color(const K& key, std::optional<Color> color) {
		return set_range_color(mmap_->lower_bound(key), mmap_->upper_bound(key), std::move(color));
	}

	// Sets color of every element
	Container& set_whole_color(std::optional<Color> color) {
		if (color.has_value())
			return set_range_color(mmap_->begin(), mmap_->end(), std::move(color));

		colors_.clear();
		return *this;
	}

	virtual LatexCode draw_as_latex() const override {
		return ContainerImplDetails::draw_as_latex("\\{", "\\}", mmap_->begin(), mmap_->end(), colors_,
			[](auto&& iter) { return &iter->first; },
			[](auto& ss, auto&& pk) {
				ss << pk.first << " \\mapsto " << pk.second;
			});
	}

	virtual HTMLCode draw_as_html() const override { throw NotImplemented(); }
};

} // namespace valgo
