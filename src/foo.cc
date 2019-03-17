#include "../include/block.h"
#include "../include/itemize.h"
#include "../include/latex.h"
#include "../include/latex_presentation.h"
#include "../include/slide_builder.h"
#include "../include/source_code.h"
#include "../include/array_1d.h"
#include "../include/variable.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace valgo;

int main() {
	LatexPresentation pres("Test", "Test presentation");
	{
		SourceCode code;
		code.set_lang("C++").set_code(
			"for (int i = 2; i < N; ++i)\n"
			"	is_prime[i] = true;\n"
			"for (int i = 2; i < N; ++i)\n"
			"	if (is_prime[i])\n"
			"		for (int j = i + i; j < N; j += i)\n"
			"			is_prime[j] = false;\n");
		Slide slide;
		slide.set_title("Sito Eratostenesa");
		slide.add_elem(
			Block("Standardowa implementacja", Color::BROWN,
				Latex("\\LaTeX~is coming..."), code));

		Itemize itmz;
		itmz.add_item(Latex("Znajduje liczby pierwsze od 2 do $N - 1$"));
		itmz.add_item(Latex("Działa w $O(n \\lg n)$"));
		slide.add_elem(itmz);

		pres.add_slide(slide);
	}

	SlideBuilder sb;
	Latex le;
	sb.add_elem(le);
	for (int i = 0; i < 4; ++i) {
		le.set("$\\sum_{i=1}^{n}{" + to_string(i) + "}$");
		pres.add_slide(sb.build());
	}

	Array1D<int> arr("tab");
	sb.add_elem(arr);
	std::vector<int> vec{3, 1, 4, 1, 5, 9, 2, 6, 5};
	arr.set(vec)
	   .set_color(4, Color::GREEN)
	   .set_color(2, Color::BLUE)
	   .set_color(7, Color::RED)
	   .set_color(1, Color::YELLOW)
	   .set_color(3, Color::BROWN);

	Array1D<int> arr2;
	sb.add_elem(arr2);
	arr2.set(vec)
	    .set_whole_array_color(Color::YELLOW)
	    .set_range_color(2, 4, Color::BROWN)
	    .set_range_color(5, 6, std::nullopt);

	Variable<double> var("pi");
	var.set(3.14159265);
	sb.add_elem(var);

	pres.add_slide(sb.build());

	pres.author("Dream team");
	pres.date("12.03.2019");
	pres.institute("MIMUW");
	cout << pres.to_str() << endl;
}
