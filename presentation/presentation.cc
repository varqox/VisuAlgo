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

int main() {
	LatexPresentation pres("Visualization of algorithms in C++", "VisuAlgo");
	// TODO: add some sensible slides :)

	pres.author(R"=(Piotr Borowski\\Michał Niciejewski\\Krzysztof Małysa\\Philip Smolenski-Jensen)=");
	pres.footer_author("Dream Team");
	pres.date("10.06.2019");
	pres.institute("Uniwersytet Warszawski, Wydział Matematyki, Informatyki i Mechaniki");
	pres.footer_institute("MIMUW");
	cout << pres.to_str() << endl;
	return 0;
}
