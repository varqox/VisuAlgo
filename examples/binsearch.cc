#include "../include/latex.h"
#include "../include/latex_presentation.h"
#include "../include/slide_builder.h"
#include "../include/array_1d.h"
#include "../include/variable.h"


#include <iostream>
#include <vector>

using namespace std;
using namespace valgo;

LatexPresentation pres("Visualization of Binary Search", "Binary search");
SlideBuilder sb;

int main() {
	int sz = 9;
	Array1D<int> bins("Binary Search", 0);
	Variable<int> szukamy("szukamy");
	Variable<int> lewy("lewy");
	Variable<int> prawy("prawy");
	sb.add_elem(bins);
	sb.add_elem(szukamy);
	sb.add_elem(lewy);
	sb.add_elem(prawy);

	vector<int> b = {1, 3, 7, 9, 10, 15, 18, 20, 21, 22};
	bins.resize(b.size());
	for (size_t i = 0; i < b.size(); ++i)
		bins.set_elem(i, b[i]);

	szukamy.set(sz);

	int l = 0, r = b.size() - 1;
	while (l < r) {
		lewy.set(l);
		prawy.set(r);
		int mid = (l + r + 1) / 2;
		bins.set_whole_array_color(std::nullopt);
		bins.set_range_color(l, r, Color::LIGHT_GREEN);
		pres.add_slide(sb.build().set_title("Binary Search"));
		bins.set_color(mid, Color::LIGHT_YELLOW);
		pres.add_slide(sb.build().set_title("Binary Search"));
		if (b[mid] <= sz) {
			l = mid;
		}
		else {
			r = mid - 1;
		}
	}

	lewy.set(l);
	prawy.set(r);
	int mid = (l + r + 1) / 2;
	bins.set_whole_array_color(std::nullopt);
	bins.set_range_color(l, r, Color::LIGHT_GREEN);
	pres.add_slide(sb.build().set_title("Binary Search"));
	bins.set_color(mid, Color::LIGHT_YELLOW);
	pres.add_slide(sb.build().set_title("Binary Search"));

	sb.remove_all_elements();

	pres.author("Dream team");
	pres.date("12.03.2019");
	pres.institute("MIMUW");
	cout << pres.to_str() << endl;
	return 0;
}