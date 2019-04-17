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

	std::set<char> myset;
	Container set_elem(myset);
	sb.add_elem(set_elem);
	myset.emplace('b');
	set_elem.set_color('b', Color::GREEN);
	pres.add_slide(sb.build().set_title("std::set<char>"));
	myset.emplace('a');
	pres.add_slide(sb.build().set_title("std::set<char>"));
	myset.emplace('c');
	pres.add_slide(sb.build().set_title("std::set<char>"));
	myset.erase('b');
	pres.add_slide(sb.build().set_title("std::set<char>"));
	myset.emplace('b');
	pres.add_slide(sb.build().set_title("std::set<char>"));
	sb.remove_all_elements();

	pres.author("Dream team");
	pres.date("17.04.2019");
	pres.institute("MIMUW");
	cout << pres.to_str() << endl;
	return 0;
}