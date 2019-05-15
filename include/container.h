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

class ContainerBase : public SlideElement {
protected:
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
};

class ContainerWithColorsMap : public ContainerBase {
public:
	using ColorMap = std::map<const void*, std::optional<Color>>;

protected:
	ColorMap colors_;

	template<class Iter>
	void copy_colors(const ColorMap& other_colors, Iter my_beg, Iter my_end, Iter other_beg) {
		colors_.clear();
		for (; my_beg != my_end; ++my_beg, ++other_beg) {
			auto col = other_colors.find(&*other_beg);
			if (col != other_colors.end())
				colors_.emplace(&*my_beg, col->second);
		}
	}

	// prints elements [beg, end) with corresponding colors: *(beg + i) with color colors_[&*(beg + i)]
	template<class Iter, class Printer>
	LatexCode draw_as_latex(const char* beg_str, const char* end_str, Iter beg, Iter end, Printer&& printer) const {
		static_assert(std::is_invocable_r_v<void, Printer, std::stringstream&,
			const typename std::iterator_traits<Iter>::value_type&>);

		std::stringstream res;
		res << "\\begin{equation*}\n" << beg_str;

		for (auto i = beg; i != end; ++i) {
			if (i != beg)
				res << ',';

			auto it = colors_.find(&*i);
			if (it != colors_.end()) {
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

	// prints elements [beg, end) with corresponding colors: *(beg + i) with color colors_[&*(beg + i)]
	template<class Iter>
	LatexCode draw_as_latex(
		const char* beg_str, const char* end_str, Iter beg, Iter end) const {
		return draw_as_latex(beg_str, end_str, beg, end, [](auto& ss, auto&& val) { ss << val; });
	}
};

template<class T>
class ColorWiseAllocator : private std::allocator<T> {
private:
	using ColorsPtr = ContainerWithColorsMap::ColorMap*;
	ColorsPtr colors_;
	using Alloc = std::allocator<T>;

	template<class U>
	friend class ColorWiseAllocator;

public:
	using value_type = typename Alloc::value_type;
	using propagate_on_container_move_assignment = std::true_type;
	using propagate_on_container_swap = std::true_type;
	using is_always_equal = std::false_type;

	ColorWiseAllocator(ColorsPtr colors) noexcept : colors_(colors) {}

	ColorWiseAllocator(const ColorWiseAllocator&) noexcept = default;
	ColorWiseAllocator(ColorWiseAllocator&&) noexcept = default;
	ColorWiseAllocator& operator=(const ColorWiseAllocator&) noexcept = default;
	ColorWiseAllocator& operator=(ColorWiseAllocator&&) noexcept = default;

	template<class U>
	ColorWiseAllocator(const ColorWiseAllocator<U>& m) noexcept : Alloc(m), colors_(m.colors_) {}

	ColorWiseAllocator select_on_container_copy_construction() const noexcept {
		return ColorWiseAllocator(nullptr);
	}

	using Alloc::allocate;

	void deallocate(T* p, std::size_t n) noexcept {
		auto it = colors_->lower_bound(p);
		while (it != colors_->end() and it->first < p + n) {
			// Found colored address in the deallocated memory segment
			colors_->erase(it++);
		}

		Alloc::deallocate(p, n);
	}

	template<class A, class B>
	friend bool operator==(const ColorWiseAllocator<A>& a, const ColorWiseAllocator<B>& b) noexcept;

	template<class A, class B>
	friend bool operator!=(const ColorWiseAllocator<A>& a, const ColorWiseAllocator<B>& b) noexcept;
};

template<class A, class B>
inline bool operator==(const ColorWiseAllocator<A>& a, const ColorWiseAllocator<B>& b) noexcept {
	return (Alloc(a) == Alloc(b) and a.colors_ == b.colors_);
}

template<class A, class B>
inline bool operator!=(const ColorWiseAllocator<A>& a, const ColorWiseAllocator<B>& b) noexcept {
	return (Alloc(a) != Alloc(b) or a.colors_ != b.colors_);
}

template<class T>
class Container;

template<class T, size_t N>
class Container<std::array<T, N>> : public ContainerBase, public std::array<T, N> {
private:
	using Array = std::array<T, N>;
	std::array<std::optional<Color>, N> colors_ = {{}};

public:
	Container() = default;

	Container(const Array& a) : Array(a) {}

	Container& operator=(const Array& a) {
		Array::operator=(a);
		return *this;
	}

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
		return ContainerBase::draw_as_latex(Array::begin(), Array::end(), colors_.begin(), colors_.end());
	}

	virtual HTMLCode draw_as_html() const override { throw NotImplemented(); }
};

template<class T>
class Container<std::vector<T>> : public ContainerBase, public std::vector<T> {
private:
	using Vector = std::vector<T>;
	std::vector<std::optional<Color>> colors_;

public:
	Container() = default;

	using Vector::Vector;

	Container& operator=(std::initializer_list<T> ilist) {
		Vector::operator=(std::move(ilist));
		return *this;
	}

	virtual std::unique_ptr<SlideElement> clone() const override { return std::make_unique<Container>(*this); }

	Container& set_color(size_t n, std::optional<Color> color) {
		colors_.resize(Vector::size());
		colors_[n] = std::move(color);
		return *this;
	}

	// Sets color of elements in range [beg, end)
	Container& set_range_color(size_t beg, size_t end, std::optional<Color> color) {
		colors_.resize(Vector::size());
		std::fill(colors_.begin() + beg, colors_.begin() + end, std::move(color));
		return *this;
	}

	// Sets color of every element
	Container& set_whole_color(std::optional<Color> color) {
		colors_.assign(Vector::size(), std::move(color));
		return *this;
	}

	virtual LatexCode draw_as_latex() const override {
		return ContainerBase::draw_as_latex(Vector::begin(), Vector::end(), colors_.begin(), colors_.end());
	}

	virtual HTMLCode draw_as_html() const override { throw NotImplemented(); }
};

template<class T>
class Container<std::deque<T>> : public ContainerBase, public std::deque<T> {
private:
	using Deque = std::deque<T>;
	std::vector<std::optional<Color>> colors_;

public:
	Container() = default;

	using Deque::Deque;

	Container& operator=(std::initializer_list<T> ilist) {
		Deque::operator=(std::move(ilist));
		return *this;
	}

	virtual std::unique_ptr<SlideElement> clone() const override { return std::make_unique<Container>(*this); }

	Container& set_color(size_t n, std::optional<Color> color) {
		colors_.resize(Deque::size());
		colors_[n] = std::move(color);
		return *this;
	}

	// Sets color of elements in range [beg, end)
	Container& set_range_color(size_t beg, size_t end, std::optional<Color> color) {
		colors_.resize(Deque::size());
		std::fill(colors_.begin() + beg, colors_.begin() + end, std::move(color));
		return *this;
	}

	// Sets color of every element
	Container& set_whole_color(std::optional<Color> color) {
		colors_.assign(Deque::size(), std::move(color));
		return *this;
	}

	virtual LatexCode draw_as_latex() const override {
		return ContainerBase::draw_as_latex(Deque::begin(), Deque::end(), colors_.begin(), colors_.end());
	}

	virtual HTMLCode draw_as_html() const override { throw NotImplemented(); }
};

template<class T>
class Container<std::list<T>> :
	public ContainerWithColorsMap, // Important: has to appear before std::list below, because ColorWiseAllocator uses it
	public std::list<T, ColorWiseAllocator<T>> {
private:
	using List = std::list<T, ColorWiseAllocator<T>>;
	using Allocator = typename List::allocator_type;

public:
	Container() : List(Allocator(&colors_)) {}

	Container(typename List::size_type count, const T& value) : List(count, value, Allocator(&colors_)) {}

	explicit Container(typename List::size_type count) : List(count, Allocator(&colors_)) {}

	template<class Iter>
	Container(Iter first, Iter last) : List(first, last, Allocator(&colors_)) {}

	Container(std::initializer_list<T> ilist) : List(std::move(ilist), Allocator(&colors_)) {}

	Container(const Container& c) : List(c, Allocator(&colors_)) {
		ContainerWithColorsMap::copy_colors(c.colors_, List::cbegin(), List::cend(), c.cbegin());
	}

	Container(Container&&) = default;

	Container& operator=(const Container& c) { *this = Container(c); }

	Container& operator=(Container&&) = default;

	Container& operator=(std::initializer_list<T> ilist) {
		List::operator=(std::move(ilist));
		return *this;
	}

	virtual std::unique_ptr<SlideElement> clone() const override { return std::make_unique<Container>(*this); }

	Container& set_color(typename List::const_iterator it, std::optional<Color> color) {
		if (color.has_value())
			colors_[&*it] = std::move(color);
		else
			colors_.erase(&*it);

		return *this;
	}

	Container& set_color(size_t n, std::optional<Color> color) {
		if (n < List::size()) {
			auto it = List::begin();
			std::advance(it, n);
			set_color(it, std::move(color));
		}

		return *this;
	}

	// Sets color of elements in range [beg, end)
	Container& set_range_color(typename List::const_iterator beg, typename List::const_iterator end,
	                           std::optional<Color> color) {
		while (beg != end)
			set_color(beg++, color);

		return *this;
	}

	// Sets color of elements in range [beg, end)
	Container& set_range_color(size_t beg, size_t end, std::optional<Color> color) {
		auto it = List::begin();
		advance(it, beg);
		auto it2 = it;
		advance(it2, end - beg);
		set_range_color(it, it2, std::move(color));
		return *this;
	}

	// Sets color of every element
	Container& set_whole_color(std::optional<Color> color) {
		if (color.has_value())
			return set_range_color(List::begin(), List::end(), std::move(color));

		colors_.clear();
		return *this;
	}

	virtual LatexCode draw_as_latex() const override {
		return ContainerWithColorsMap::draw_as_latex("[", "]", List::begin(), List::end());
	}

	virtual HTMLCode draw_as_html() const override { throw NotImplemented(); }
};

template<class T>
class Container<std::forward_list<T>> :
	public ContainerWithColorsMap, // Important: has to appear before std::forward_list below, because ColorWiseAllocator uses it
	public std::forward_list<T, ColorWiseAllocator<T>> {
private:
	using FList = std::forward_list<T, ColorWiseAllocator<T>>;
	using Allocator = typename FList::allocator_type;

public:
	Container() : FList(Allocator(&colors_)) {}

	Container(typename FList::size_type count, const T& value) : FList(count, value, Allocator(&colors_)) {}

	explicit Container(typename FList::size_type count) : FList(count, Allocator(&colors_)) {}

	template<class Iter>
	Container(Iter first, Iter last) : FList(first, last, Allocator(&colors_)) {}

	Container(std::initializer_list<T> ilist) : FList(std::move(ilist), Allocator(&colors_)) {}

	Container(const Container& c) : FList(c, Allocator(&colors_)) {
		ContainerWithColorsMap::copy_colors(c.colors_, FList::cbegin(), FList::cend(), c.cbegin());
	}

	Container(Container&&) = default;

	Container& operator=(const Container& c) { *this = Container(c); }

	Container& operator=(Container&&) = default;

	Container& operator=(std::initializer_list<T> ilist) {
		FList::operator=(std::move(ilist));
		return *this;
	}

	virtual std::unique_ptr<SlideElement> clone() const override { return std::make_unique<Container>(*this); }

	Container& set_color(typename FList::const_iterator it, std::optional<Color> color) {
		if (color.has_value())
			colors_[&*it] = std::move(color);
		else
			colors_.erase(&*it);

		return *this;
	}

	Container& set_color(size_t n, std::optional<Color> color) {
		auto it = FList::begin();
		// advance(it, n) but check for end()
		while (n-- > 0 && it != FList::end())
			++it;

		if (it != FList::end())
			set_color(it, std::move(color));

		return *this;
	}

	// Sets color of elements in range [beg, end)
	Container& set_range_color(typename FList::const_iterator beg, typename FList::const_iterator end,
	                           std::optional<Color> color) {
		while (beg != end)
			set_color(beg++, color);

		return *this;
	}

	// Sets color of elements in range [beg, end)
	Container& set_range_color(size_t beg, size_t end, std::optional<Color> color) {
		auto it = FList::begin();
		advance(it, beg);
		auto it2 = it;
		advance(it2, end - beg);
		set_range_color(it, it2, std::move(color));
		return *this;
	}

	// Sets color of every element
	Container& set_whole_color(std::optional<Color> color) {
		if (color.has_value())
			return set_range_color(FList::begin(), FList::end(), std::move(color));

		colors_.clear();
		return *this;
	}

	virtual LatexCode draw_as_latex() const override {
		return ContainerWithColorsMap::draw_as_latex("[", "]", FList::begin(), FList::end());
	}

	virtual HTMLCode draw_as_html() const override { throw NotImplemented(); }
};

template<class T, class Compare>
class Container<std::set<T, Compare>> :
	public ContainerWithColorsMap, // Important: has to appear before std::set below, because ColorWiseAllocator uses it
	public std::set<T, Compare, ColorWiseAllocator<T>> {
private:
	using Set = std::set<T, Compare, ColorWiseAllocator<T>>;
	using Allocator = typename Set::allocator_type;

public:
	explicit Container(const Compare& comp = Compare()) : Set(comp, Allocator(&colors_)) {}

	template<class Iter>
	Container(Iter first, Iter last, const Compare& comp = Compare()) : Set(first, last, comp, Allocator(&colors_)) {}

	Container(std::initializer_list<typename Set::value_type> ilist, const Compare& comp = Compare()) : Set(std::move(ilist), comp, Allocator(&colors_)) {}

	Container(const Container& c) : Set(c, Allocator(&colors_)) {
		ContainerWithColorsMap::copy_colors(c.colors_, Set::cbegin(), Set::cend(), c.cbegin());
	}

	Container(Container&&) = default;

	Container& operator=(const Container& c) { *this = Container(c); }

	Container& operator=(Container&&) = default;

	Container& operator=(std::initializer_list<typename Set::value_type> ilist) {
		Set::operator=(std::move(ilist));
		return *this;
	}

	virtual std::unique_ptr<SlideElement> clone() const override { return std::make_unique<Container>(*this); }

	Container& set_color(typename Set::const_iterator it, std::optional<Color> color) {
		if (color.has_value())
			colors_[&*it] = std::move(color);
		else
			colors_.erase(&*it);

		return *this;
	}

	Container& set_color(const T& elem, std::optional<Color> color) {
		auto it = Set::find(elem);
		if (it != Set::end())
			set_color(std::move(it), std::move(color));

		return *this;
	}

	// Sets color of elements in range [beg, end)
	Container& set_range_color(typename Set::const_iterator beg, typename Set::const_iterator end,
	                           std::optional<Color> color) {
		while (beg != end)
			set_color(beg++, color);

		return *this;
	}

	// Sets color of every element
	Container& set_whole_color(std::optional<Color> color) {
		if (color.has_value())
			return set_range_color(Set::begin(), Set::end(), std::move(color));

		colors_.clear();
		return *this;
	}

	virtual LatexCode draw_as_latex() const override {
		return ContainerWithColorsMap::draw_as_latex("\\{", "\\}", Set::begin(), Set::end());
	}

	virtual HTMLCode draw_as_html() const override { throw NotImplemented(); }
};

template<class T, class Compare>
class Container<std::multiset<T, Compare>> :
	public ContainerWithColorsMap, // Important: has to appear before std::multiset below, because ColorWiseAllocator uses it
	public std::multiset<T, Compare, ColorWiseAllocator<T>> {
private:
	using MSet = std::multiset<T, Compare, ColorWiseAllocator<T>>;
	using Allocator = typename MSet::allocator_type;

public:
	explicit Container(const Compare& comp = Compare()) : MSet(comp, Allocator(&colors_)) {}

	template<class Iter>
	Container(Iter first, Iter last, const Compare& comp = Compare()) : MSet(first, last, comp, Allocator(&colors_)) {}

	Container(std::initializer_list<typename MSet::value_type> ilist, const Compare& comp = Compare()) : MSet(std::move(ilist), comp, Allocator(&colors_)) {}

	Container(const Container& c) : MSet(c, Allocator(&colors_)) {
		ContainerWithColorsMap::copy_colors(c.colors_, MSet::cbegin(), MSet::cend(), c.cbegin());
	}

	Container(Container&&) = default;

	Container& operator=(const Container& c) { *this = Container(c); }

	Container& operator=(Container&&) = default;

	Container& operator=(std::initializer_list<typename MSet::value_type> ilist) {
		MSet::operator=(std::move(ilist));
		return *this;
	}

	virtual std::unique_ptr<SlideElement> clone() const override { return std::make_unique<Container>(*this); }

	Container& set_color(typename MSet::const_iterator it, std::optional<Color> color) {
		if (color.has_value())
			colors_[&*it] = std::move(color);
		else
			colors_.erase(&*it);

		return *this;
	}

	// Sets color of elements in range [beg, end)
	Container& set_range_color(typename MSet::const_iterator beg,
	                           typename MSet::const_iterator end, std::optional<Color> color) {
		while (beg != end)
			set_color(beg++, color);

		return *this;
	}

	Container& set_color(const T& elem, std::optional<Color> color) {
		return set_range_color(MSet::lower_bound(elem), MSet::upper_bound(elem), std::move(color));
	}

	// Sets color of every element
	Container& set_whole_color(std::optional<Color> color) {
		if (color.has_value())
			return set_range_color(MSet::begin(), MSet::end(), std::move(color));

		colors_.clear();
		return *this;
	}

	virtual LatexCode draw_as_latex() const override {
		return ContainerWithColorsMap::draw_as_latex("\\{", "\\}", MSet::begin(), MSet::end());
	}

	virtual HTMLCode draw_as_html() const override { throw NotImplemented(); }
};

template<class K, class V, class Compare>
class Container<std::map<K, V, Compare>> :
	public ContainerWithColorsMap, // Important: has to appear before std::map below, because ColorWiseAllocator uses it
	public std::map<K, V, Compare, ColorWiseAllocator<std::pair<const K, V>>> {
private:
	using Map = std::map<K, V, Compare, ColorWiseAllocator<std::pair<const K, V>>>;
	using Allocator = typename Map::allocator_type;

public:
	explicit Container(const Compare& comp = Compare()) : Map(comp, Allocator(&colors_)) {}

	template<class Iter>
	Container(Iter first, Iter last, const Compare& comp = Compare()) : Map(first, last, comp, Allocator(&colors_)) {}

	Container(std::initializer_list<typename Map::value_type> ilist, const Compare& comp = Compare()) : Map(std::move(ilist), comp, Allocator(&colors_)) {}

	Container(const Container& c) : Map(c, Allocator(&colors_)) {
		ContainerWithColorsMap::copy_colors(c.colors_, Map::cbegin(), Map::cend(), c.cbegin());
	}

	Container(Container&&) = default;

	Container& operator=(const Container& c) { *this = Container(c); }

	Container& operator=(Container&&) = default;

	Container& operator=(std::initializer_list<typename Map::value_type> ilist) {
		Map::operator=(std::move(ilist));
		return *this;
	}

	virtual std::unique_ptr<SlideElement> clone() const override { return std::make_unique<Container>(*this); }

	Container& set_color(typename Map::const_iterator it, std::optional<Color> color) {
		if (color.has_value())
			colors_[&*it] = std::move(color);
		else
			colors_.erase(&*it);

		return *this;
	}

	Container& set_color(const K& key, std::optional<Color> color) {
		auto it = Map::find(key);
		if (it != Map::end())
			set_color(std::move(it), std::move(color));

		return *this;
	}

	// Sets color of elements in range [beg, end)
	Container& set_range_color(typename Map::const_iterator beg, typename Map::const_iterator end,
	                           std::optional<Color> color) {
		while (beg != end)
			set_color(beg++, color);

		return *this;
	}

	// Sets color of every element
	Container& set_whole_color(std::optional<Color> color) {
		if (color.has_value())
			return set_range_color(Map::begin(), Map::end(), std::move(color));

		colors_.clear();
		return *this;
	}

	virtual LatexCode draw_as_latex() const override {
		return ContainerWithColorsMap::draw_as_latex("\\{", "\\}", Map::begin(), Map::end(), [](auto& ss, auto&& pk) {
				ss << pk.first << " \\mapsto " << pk.second;
			});
	}

	virtual HTMLCode draw_as_html() const override { throw NotImplemented(); }
};

template<class K, class V, class Compare>
class Container<std::multimap<K, V, Compare>> :
	public ContainerWithColorsMap, // Important: has to appear before std::multimap below, because ColorWiseAllocator uses it
	public std::multimap<K, V, Compare, ColorWiseAllocator<std::pair<const K, V>>> {
private:
	using MMap = std::multimap<K, V, Compare, ColorWiseAllocator<std::pair<const K, V>>>;
	using Allocator = typename MMap::allocator_type;

public:
	explicit Container(const Compare& comp = Compare()) : MMap(comp, Allocator(&colors_)) {}

	template<class Iter>
	Container(Iter first, Iter last, const Compare& comp = Compare()) : MMap(first, last, comp, Allocator(&colors_)) {}

	Container(std::initializer_list<typename MMap::value_type> ilist, const Compare& comp = Compare()) : MMap(std::move(ilist), comp, Allocator(&colors_)) {}

	Container(const Container& c) : MMap(c, Allocator(&colors_)) {
		ContainerWithColorsMap::copy_colors(c.colors_, MMap::cbegin(), MMap::cend(), c.cbegin());
	}

	Container(Container&&) = default;

	Container& operator=(const Container& c) { *this = Container(c); }

	Container& operator=(Container&&) = default;

	Container& operator=(std::initializer_list<typename MMap::value_type> ilist) {
		MMap::operator=(std::move(ilist));
		return *this;
	}

	virtual std::unique_ptr<SlideElement> clone() const override { return std::make_unique<Container>(*this); }

	Container& set_color(typename MMap::const_iterator it, std::optional<Color> color) {
		if (color.has_value())
			colors_[&it->first] = std::move(color);
		else
			colors_.erase(&it->first);

		return *this;
	}

	// Sets color of elements in range [beg, end)
	Container& set_range_color(typename MMap::const_iterator beg,
	                           typename MMap::const_iterator end, std::optional<Color> color) {
		while (beg != end)
			set_color(beg++, color);

		return *this;
	}

	Container& set_color(const K& key, std::optional<Color> color) {
		return set_range_color(MMap::lower_bound(key), MMap::upper_bound(key), std::move(color));
	}

	// Sets color of every element
	Container& set_whole_color(std::optional<Color> color) {
		if (color.has_value())
			return set_range_color(MMap::begin(), MMap::end(), std::move(color));

		colors_.clear();
		return *this;
	}

	virtual LatexCode draw_as_latex() const override {
		return ContainerWithColorsMap::draw_as_latex("\\{", "\\}", MMap::begin(), MMap::end(), [](auto& ss, auto&& pk) {
				ss << pk.first << " \\mapsto " << pk.second;
			});
	}

	virtual HTMLCode draw_as_html() const override { throw NotImplemented(); }
};

} // namespace valgo
