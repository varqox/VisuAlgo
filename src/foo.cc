#include "../include/latex_element.h"
#include "../include/latex_presentation.h"
#include "../include/slide_builder.h"
#include "../include/source_code_element.h"

#include <iostream>

using namespace std;
using namespace valgo;

int main() {
	LatexPresentation pres("Test", "Test presentation");
	pres.add_slide(Slide(SourceCodeElement().set_lang("C++").set_code(
		"for (int i = 2; i < N; ++i)\n"
		"	is_prime[i] = true;\n"
		"for (int i = 2; i < N; ++i)\n"
		"	if (is_prime[i])\n"
		"		for (int j = i + i; j < N; j += i)\n"
		"			is_prime[j] = false;\n")).set_title("Sito Eratostenesa"));

	SlideBuilder sb;
	LatexElement le;
	sb.add_element(le);
	for (int i = 0; i < 4; ++i) {
		le.set("$\\sum_{i=1}^{n}{" + to_string(i) + "}$");
		pres.add_slide(sb.build());
	}

	pres.author("Dream team");
	pres.date("12.03.2019");
	pres.institute("MIMUW");
	cout << pres.to_str() << std::endl;
}
