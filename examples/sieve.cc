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

LatexPresentation pres("Visualization of Sieve of Erathostenes", "Sieve");
SlideBuilder sb;

int main() {
	SourceCode code;
	code.set_lang("C++").set_code(
			"for (int i = 2; i < N; ++i)\n"
			"	is_prime[i] = true;\n"
			"for (int i = 2; i < N; ++i)\n"
			"	if (is_prime[i])\n"
			"		for (int j = i + i; j < N; j += i)\n"
			"			is_prime[j] = false;\n");
	Slide slide;
	slide.set_title("Sieve of Erathostenes");
	slide.add_elem(
			Block("Standardowa implementacja", Color::LIGHT_BROWN,
				  Latex("\\LaTeX~is coming..."), code));

	Itemize itmz;
	itmz.add_item(Latex("Znajduje liczby pierwsze od 2 do $N - 1$"));
	itmz.add_item(Latex("Działa w $O(n \\lg n)$"));
	slide.add_elem(itmz);

	pres.add_slide(slide);

	constexpr int N = 12;
	Array1D<bool> vtab("pierwsza", N);
	sb.add_elem(vtab);
	for (int i = 2; i < N; ++i)
		vtab.set_elem(i, true);

	vector<bool> is_prime(N, true);
	is_prime[0] = is_prime[1] = false;
	vtab.set_color(0, Color::LIGHT_RED);
	vtab.set_color(1, Color::LIGHT_RED);
	pres.add_slide(sb.build().set_title("Sieve of Erathostenes"));
	Variable<int> wyk("wykreślmy wielokrotności");
	sb.add_elem(wyk);

	for (int i = 2; i < N; ++i) {
		if (is_prime[i]) {
			wyk.set(i);
			vtab.set_color(i, Color::LIGHT_YELLOW);
			pres.add_slide(sb.build().set_title("Sieve of Erathostenes"));
			for (int j = i + i; j < N; j += i) {
				Variable<int> wyk2("teraz wykreśliliśmy");
				wyk2.set(j);
				sb.add_elem(wyk2);
				is_prime[j] = false;
				vtab.set_color(j, Color::LIGHT_RED);
				vtab.set_elem(j, false);
				pres.add_slide(sb.build().set_title("Sieve of Erathostenes"));
				sb.remove_elem(wyk2);
			}
		}
	}

	sb.remove_all_elements();

	pres.author("Dream team");
	pres.date("12.03.2019");
	pres.institute("MIMUW");
	cout << pres.to_str() << endl;
	return 0;
}