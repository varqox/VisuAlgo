#include "../include/latex.h"
#include "../include/latex_presentation.h"
#include "../include/slide_builder.h"
#include "../include/matrix.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace valgo;

LatexPresentation pres("Visualization of matrices", "Matrices");
SlideBuilder sb;

int main() {
	Matrix<int> m(5, 7);
	sb.add_elem(m);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 7; j++) {
			m.set_elem(i, j, (i + 1) * (j + 1));
		}
	}

	pres.add_slide(sb.build());

	m.set_columns(5);
	pres.add_slide(sb.build());



	m.set_rows(3);
	pres.add_slide(sb.build());

	m.set_rows(7);
	m.set_columns(7);



	Matrix<double> n(5, 7);
	sb.add_elem(n);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 7; j++) {
			n.set_elem(i, j, (double)(i + 1) / (double)(j + 1));
		}
	}

	pres.add_slide(sb.build());

	Matrix<string> o(5, 7);
	sb.add_elem(o);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 7; j++) {
			o.set_elem(i, j, "ala");
		}
	}

	pres.add_slide(sb.build());
	cout << pres.to_str() << endl;

	return 0;
}