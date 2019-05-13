#include "../include/container.h"
#include "../include/latex_presentation.h"
#include "../include/slide_builder.h"

#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
using namespace valgo;

LatexPresentation pres("Containers", "Containers");
SlideBuilder sb;

int main() {
	vector vec = {1, 2, 3};
	Container vec_elem(vec);
	sb.add_elem(vec_elem);

	pres.add_slide(sb.build().set_title("std::vector<int>"));
	vec_elem.set_color(0, Color::RED);
	pres.add_slide(sb.build().set_title("std::vector<int>"));
	vec_elem.set_color(2, Color::GREEN);
	pres.add_slide(sb.build().set_title("std::vector<int>"));
	vec.pop_back();
	pres.add_slide(sb.build().set_title("std::vector<int>"));
	vec.emplace_back(4);
	pres.add_slide(sb.build().set_title("std::vector<int>"));
	sb.remove_all_elements();

	array<short, 20> arr;
	std::iota(arr.begin(), arr.end(), 0);
	Container arr_elem(arr);
	sb.add_elem(arr_elem);
	arr_elem.set_whole_color(Color::RED);
	arr_elem.set_range_color(5, 12, Color::BLACK);
	arr_elem.set_color(8, Color::GREEN);
	pres.add_slide(sb.build().set_title("std::array<short>"));
	sb.remove_all_elements();

	std::deque<char> deq;
	Container deq_elem(deq);
	sb.add_elem(deq_elem);
	deq.push_back('a');
	deq_elem.set_color(0, Color::GREEN);
	pres.add_slide(sb.build().set_title("std::deque<char>"));
	deq.push_front('b');
	deq.push_back('c');
	deq.push_back('d');
	deq.push_back('e');
	pres.add_slide(sb.build().set_title("std::deque<char>"));
	deq_elem.set_range_color(2, 4, Color::RED);
	pres.add_slide(sb.build().set_title("std::deque<char>"));
	sb.remove_all_elements();

	std::list<char> list;
	Container list_elem(list);
	sb.add_elem(list_elem);
	list.push_back('a');
	list_elem.set_color(0, Color::GREEN);
	pres.add_slide(sb.build().set_title("std::list<char>"));
	list.push_front('b');
	list.push_back('c');
	list.push_back('d');
	list.push_back('e');
	pres.add_slide(sb.build().set_title("std::list<char>"));
	list_elem.set_range_color(2, 4, Color::RED);
	pres.add_slide(sb.build().set_title("std::list<char>"));
	sb.remove_all_elements();

	std::forward_list<char> flist;
	Container flist_elem(flist);
	sb.add_elem(flist_elem);
	flist.emplace_front('e');
	flist.emplace_front('d');
	flist.emplace_front('c');
	flist.emplace_front('b');
	flist_elem.set_color(0, Color::GREEN);
	pres.add_slide(sb.build().set_title("std::forward\\_list<char>"));
	flist.emplace_front('a');
	pres.add_slide(sb.build().set_title("std::forward\\_list<char>"));
	flist_elem.set_range_color(2, 4, Color::RED);
	pres.add_slide(sb.build().set_title("std::forward\\_list<char>"));
	sb.remove_all_elements();

	std::set<char> myset;
	Container set_elem(myset);
	sb.add_elem(set_elem);
	myset.emplace('k');
	set_elem.set_color('k', Color::GREEN);
	pres.add_slide(sb.build().set_title("std::set<char>"));
	myset.emplace('f');
	pres.add_slide(sb.build().set_title("std::set<char>"));
	myset.emplace('p');
	pres.add_slide(sb.build().set_title("std::set<char>"));
	myset.erase('k');
	pres.add_slide(sb.build().set_title("std::set<char>"));
	myset.emplace('k');
	pres.add_slide(sb.build().set_title("std::set<char>"));
	for (char c : std::string("abcdefghijklmnopqrstuvwxyz"))
		myset.emplace(c);
	pres.add_slide(sb.build().set_title("std::set<char>"));
	set_elem.set_range_color(myset.lower_bound('c'), myset.upper_bound('o'), Color::RED);
	pres.add_slide(sb.build().set_title("std::set<char>"));
	sb.remove_all_elements();

	std::multiset<char> mymset;
	Container mset_elem(mymset);
	sb.add_elem(mset_elem);
	for (char c : std::string("aaabbcccdeeefff"))
		mymset.emplace(c);
	mset_elem.set_color('c', Color::GREEN);
	pres.add_slide(sb.build().set_title("std::multiset<char>"));
	mset_elem.set_color(mymset.begin(), Color::RED);
	pres.add_slide(sb.build().set_title("std::multiset<char>"));
	mset_elem.set_color(mymset.find('e'), Color::BLUE);
	pres.add_slide(sb.build().set_title("std::multiset<char>"));
	mset_elem.set_color(++mymset.lower_bound('f'), Color::MAGENTA);
	pres.add_slide(sb.build().set_title("std::multiset<char>"));
	sb.remove_all_elements();

	std::map<char, int> mymap;
	Container map_elem(mymap);
	sb.add_elem(map_elem);
	mymap.emplace('k', 'k' - 'a');
	map_elem.set_color('k', Color::GREEN);
	pres.add_slide(sb.build().set_title("std::map<char, int>"));
	mymap.emplace('f', 'f' - 'a');
	pres.add_slide(sb.build().set_title("std::map<char, int>"));
	mymap.emplace('p', 'p' - 'a');
	pres.add_slide(sb.build().set_title("std::map<char, int>"));
	mymap.erase('k');
	// TODO: remove unused colors when (multi)?(set|map) is drawn
	pres.add_slide(sb.build().set_title("std::map<char, int>"));
	mymap.emplace('k', 'k' - 'a');
	pres.add_slide(sb.build().set_title("std::map<char, int>"));
	for (char c : std::string("abcdefgh"))
		mymap.emplace(c, int(c - 'a'));
	pres.add_slide(sb.build().set_title("std::map<char, int>"));
	map_elem.set_range_color(mymap.lower_bound('c'), mymap.upper_bound('f'), Color::RED);
	pres.add_slide(sb.build().set_title("std::map<char, int>"));
	sb.remove_all_elements();

	std::multimap<char, int> mymmap;
	Container mmap_elem(mymmap);
	sb.add_elem(mmap_elem);
	for (char c : std::string("aabccdeeff"))
		mymmap.emplace(c, int(c - 'a'));
	mmap_elem.set_color('c', Color::GREEN);
	pres.add_slide(sb.build().set_title("std::multimap<char, int>"));
	mmap_elem.set_color(mymmap.begin(), Color::RED);
	pres.add_slide(sb.build().set_title("std::multimap<char, int>"));
	mmap_elem.set_color(mymmap.find('e'), Color::BLUE);
	pres.add_slide(sb.build().set_title("std::multimap<char, int>"));
	mmap_elem.set_color(++mymmap.lower_bound('f'), Color::MAGENTA);
	pres.add_slide(sb.build().set_title("std::multimap<char, int>"));
	sb.remove_all_elements();

	pres.author("Dream team");
	pres.date("17.04.2019");
	pres.institute("MIMUW");
	cout << pres.to_str() << endl;
	return 0;
}