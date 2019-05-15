#include "../include/container.h"
#include "../include/latex_presentation.h"
#include "../include/slide_builder.h"

#include <iostream>
#include <numeric>
#include <vector>

using namespace valgo;

LatexPresentation pres("Containers", "Containers");
SlideBuilder sb;

int main() {
	Container<std::vector<int>> vector = {1, 2, 3};
	sb.add_elem(vector);

	pres.add_slide(sb.build().set_title("std::vector<int>"));
	vector.set_color(0, Color::RED);
	pres.add_slide(sb.build().set_title("std::vector<int>"));
	vector.set_color(2, Color::GREEN);
	pres.add_slide(sb.build().set_title("std::vector<int>"));
	vector.pop_back();
	pres.add_slide(sb.build().set_title("std::vector<int>"));
	vector.emplace_back(4);
	pres.add_slide(sb.build().set_title("std::vector<int>"));
	sb.remove_all_elements();

	Container<std::array<short, 20>> array;
	std::iota(array.begin(), array.end(), 0);
	sb.add_elem(array);
	array.set_whole_color(Color::RED);
	array.set_range_color(5, 12, Color::BLACK);
	array.set_color(8, Color::GREEN);
	pres.add_slide(sb.build().set_title("std::array<short>"));
	sb.remove_all_elements();

	Container<std::deque<char>> deque;
	sb.add_elem(deque);
	deque.push_back('a');
	deque.set_color(0, Color::GREEN);
	pres.add_slide(sb.build().set_title("std::deque<char>"));
	deque.push_front('b');
	deque.push_back('c');
	deque.push_back('d');
	deque.push_back('e');
	pres.add_slide(sb.build().set_title("std::deque<char>"));
	deque.set_range_color(2, 4, Color::RED);
	pres.add_slide(sb.build().set_title("std::deque<char>"));
	sb.remove_all_elements();

	Container<std::list<char>> list;
	sb.add_elem(list);
	list.push_back('a');
	list.set_color(0, Color::GREEN);
	pres.add_slide(sb.build().set_title("std::list<char>"));
	list.push_front('b');
	list.push_back('c');
	list.push_back('d');
	list.push_back('e');
	pres.add_slide(sb.build().set_title("std::list<char>"));
	list.set_range_color(2, 4, Color::RED);
	pres.add_slide(sb.build().set_title("std::list<char>"));
	sb.remove_all_elements();

	Container<std::forward_list<char>> frd_list;
	sb.add_elem(frd_list);
	frd_list.emplace_front('e');
	frd_list.emplace_front('d');
	frd_list.emplace_front('c');
	frd_list.emplace_front('b');
	frd_list.set_color(0, Color::GREEN);
	pres.add_slide(sb.build().set_title("std::forward\\_list<char>"));
	frd_list.emplace_front('a');
	pres.add_slide(sb.build().set_title("std::forward\\_list<char>"));
	frd_list.set_range_color(2, 4, Color::RED);
	pres.add_slide(sb.build().set_title("std::forward\\_list<char>"));
	sb.remove_all_elements();

	Container<std::set<char>> set;
	sb.add_elem(set);
	set.emplace('k');
	set.set_color('k', Color::GREEN);
	pres.add_slide(sb.build().set_title("std::set<char>"));
	set.emplace('f');
	pres.add_slide(sb.build().set_title("std::set<char>"));
	set.emplace('p');
	pres.add_slide(sb.build().set_title("std::set<char>"));
	set.erase('k');
	pres.add_slide(sb.build().set_title("std::set<char>"));
	set.emplace('k');
	pres.add_slide(sb.build().set_title("std::set<char>"));
	for (char c : std::string("abcdefghijklmnopqrstuvwxyz"))
		set.emplace(c);
	pres.add_slide(sb.build().set_title("std::set<char>"));
	set.set_range_color(set.lower_bound('c'), set.upper_bound('o'), Color::RED);
	pres.add_slide(sb.build().set_title("std::set<char>"));
	sb.remove_all_elements();

	Container<std::multiset<char>> multiset;
	sb.add_elem(multiset);
	for (char c : std::string("aaabbcccdeeefff"))
		multiset.emplace(c);
	multiset.set_color('c', Color::GREEN);
	pres.add_slide(sb.build().set_title("std::multiset<char>"));
	multiset.set_color(multiset.begin(), Color::RED);
	pres.add_slide(sb.build().set_title("std::multiset<char>"));
	multiset.set_color(multiset.find('e'), Color::BLUE);
	pres.add_slide(sb.build().set_title("std::multiset<char>"));
	multiset.set_color(++multiset.lower_bound('f'), Color::MAGENTA);
	pres.add_slide(sb.build().set_title("std::multiset<char>"));
	sb.remove_all_elements();

	Container<std::map<char, int>> map;
	sb.add_elem(map);
	map.emplace('k', 'k' - 'a');
	map.set_color('k', Color::GREEN);
	pres.add_slide(sb.build().set_title("std::map<char, int>"));
	map.emplace('f', 'f' - 'a');
	pres.add_slide(sb.build().set_title("std::map<char, int>"));
	map.emplace('p', 'p' - 'a');
	pres.add_slide(sb.build().set_title("std::map<char, int>"));
	map.erase('k');
	pres.add_slide(sb.build().set_title("std::map<char, int>"));
	map.emplace('k', 'k' - 'a');
	pres.add_slide(sb.build().set_title("std::map<char, int>"));
	for (char c : std::string("abcdefgh"))
		map.emplace(c, int(c - 'a'));
	pres.add_slide(sb.build().set_title("std::map<char, int>"));
	map.set_range_color(map.lower_bound('c'), map.upper_bound('f'), Color::RED);
	pres.add_slide(sb.build().set_title("std::map<char, int>"));
	sb.remove_all_elements();

	Container<std::multimap<char, int>> multimap;
	sb.add_elem(multimap);
	for (char c : std::string("aabccdeeff"))
		multimap.emplace(c, int(c - 'a'));
	multimap.set_color('c', Color::GREEN);
	pres.add_slide(sb.build().set_title("std::multimap<char, int>"));
	multimap.set_color(multimap.begin(), Color::RED);
	pres.add_slide(sb.build().set_title("std::multimap<char, int>"));
	multimap.set_color(multimap.find('e'), Color::BLUE);
	pres.add_slide(sb.build().set_title("std::multimap<char, int>"));
	multimap.set_color(++multimap.lower_bound('f'), Color::MAGENTA);
	pres.add_slide(sb.build().set_title("std::multimap<char, int>"));
	sb.remove_all_elements();

	pres.author("Dream team");
	pres.date("17.04.2019");
	pres.institute("MIMUW");
	std::cout << pres.to_str() << std::endl;
	return 0;
}