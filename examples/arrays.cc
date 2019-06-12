#include "../include/block.h"
#include "../include/itemize.h"
#include "../include/latex.h"
#include "../include/latex_presentation.h"
#include "../include/slide_builder.h"
#include "../include/source_code.h"
#include "../include/array_1d.h"
#include "../include/variable.h"
#include "../include/array_2d.h"
#include "../include/undirected_graph.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace valgo;


void visualize_kmp(LatexPresentation &pres, const string& str) {
	SlideBuilder sb;
	const int n = str.size();
	Array2D<string> vpi("KMP");
	Variable<int> vps("najdłuższy prefikso-sufiks");
	sb.add_elem(vpi);
	vpi.resize(4, n);
	vector<int> pi(n, -1);
	for (int i = 0; i < n; i++)
		vpi.set_elem(0, i, string(1, str[i]));
	vpi.set_color(1, 0, Color::YELLOW);

	pres.add_slide(sb.build().set_title("KMP"));

	vpi.set_elem(1, 0, to_string(-1));
	vpi.set_color(1, 0, {});

	pres.add_slide(sb.build().set_title("KMP"));

	int ps = -1;
	sb.add_elem(vps);
	vps.set(ps);
	for (int i = 1; i < n; i++) {
		vpi.set_color(1, i, Color::YELLOW);
		if (ps != -1) {
			vpi.set_color_range(2, 0, 2, ps, Color::LIGHT_GREEN);
			vpi.set_color_range(3, i - ps - 1, 3, i - 1, Color::LIGHT_GREEN);
		}
		pres.add_slide(sb.build().set_title("KMP"));
		while (ps >= 0 && str[ps + 1] != str[i]) {
			int prev_ps = ps;
			vpi.set_color(2, ps + 1, Color::LIGHT_RED);
			vpi.set_color(3, i, Color::LIGHT_RED);
			pres.add_slide(sb.build().set_title("KMP"));
			vpi.set_color(1, ps, Color::LIGHT_BROWN);
			if (pi[ps] != -1) {
				vpi.set_color_range(2, 0, 2, pi[ps], Color(92, 173, 67));
				vpi.set_color_range(3, i - pi[ps] - 1, 3, i - 1, Color(92, 173, 67));
			}
			pres.add_slide(sb.build().set_title("KMP"));
			ps = pi[ps];
			vps.set(ps);
			vpi.set_row_color(2, {});
			vpi.set_row_color(3, {});
			if (ps != -1) {
				vpi.set_color_range(2, 0, 2, ps, Color::LIGHT_GREEN);
				vpi.set_color_range(3, i - ps - 1, 3, i - 1, Color::LIGHT_GREEN);
			}
			vpi.set_color(1, prev_ps, {});
			pres.add_slide(sb.build().set_title("KMP"));
		}
		if (str[ps + 1] == str[i]) {
			vpi.set_color(2, ps + 1, Color::GREEN);
			vpi.set_color(3, i, Color::GREEN);
			pres.add_slide(sb.build().set_title("KMP"));
			ps++;
		}
		else {
			vpi.set_color(2, ps + 1, Color::RED);
			vpi.set_color(3, i, Color::RED);
			pres.add_slide(sb.build().set_title("KMP"));
		}
		pi[i] = ps;
		vps.set(ps);
		vpi.set_elem(1, i, to_string(pi[i]));
		vpi.set_whole_array_color({});
		pres.add_slide(sb.build().set_title("KMP"));
	}
	sb.remove_all_elements();
}

int main() {
	LatexPresentation pres("Visualization of arrays", "Arrays");
	SlideBuilder sb;
	Array1D<int> arr("array");
	sb.add_elem(arr);
	std::vector<int> vec{3, 1, 4, 1, 5, 9, 2, 6, 5};
	arr.set(vec)
			.set_color(4, Color::LIGHT_GREEN)
			.set_color(2, Color::LIGHT_BLUE)
			.set_color(7, Color::LIGHT_RED)
			.set_color(1, Color::LIGHT_YELLOW)
			.set_color(3, Color::LIGHT_BROWN);

	Array1D<int> arr2;
	sb.add_elem(arr2);
	arr2.set(vec)
			.set_whole_array_color(Color::LIGHT_YELLOW)
			.set_range_color(2, 4, Color::LIGHT_BROWN)
			.set_range_color(5, 6, {});

	Variable<double> var("pi");
	var.set(3.14159265);
	sb.add_elem(var);

	pres.add_slide(sb.build().set_title("Arrays"));

	Array2D<int> arr3("Array2D");
	arr3.resize (5, 10);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			arr3.set_elem(i, j, 10 * (i + j) + i);
		}
	}
	arr3.set_row_color(3, Color::LIGHT_BLUE);
	arr3.set_column_color(4, Color::LIGHT_RED);
	arr3.set_color(3, 4, Color::LIGHT_BROWN);

	sb.add_elem(arr3);
	pres.add_slide(sb.build().set_title("Arrays"));

	sb.remove_all_elements();

	visualize_kmp(pres, "abababbabb");
	visualize_kmp(pres, "abacabacabab");

	pres.author("Dream team");
	pres.date("12.03.2019");
	pres.institute("MIMUW");
	cout << pres.to_str() << endl;
	return 0;
}
/*
*/
