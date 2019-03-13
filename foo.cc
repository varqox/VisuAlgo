#include "include/latex_element.h"
#include "include/latex_presentation.h"
#include "include/slide_builder.h"

#include <iostream>

using namespace std;
using namespace valgo;

int main() {
	LatexPresentation pres("Test", "Test presentation");
	SlideBuilder sb;
	LatexElement le;
	sb.add_element(le);
	for (int i = 0; i < 4; ++i) {
		le.set('$' + to_string(i) + '$');
		pres.add_slide(sb.build());
	}

	pres.author("Dream team");
	pres.date("33.25.9999");
	pres.institute("MIMUW");
	cout << pres.to_str() << std::endl;
}
