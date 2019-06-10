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
#include "../include/image.h"
#include "../include/image_set.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace valgo;

void add_diagrams(LatexPresentation& pres) {
	{
		Image im("./io_stuff/architecture/" ,"Logical_View.pdf");
		im.set_height(6);
		im.set_width(12);
		ImageSet imset;
		imset.add_image(im);
		pres.add_slide(Slide(imset).set_title("Architecture - logical view"));
	}
	{
		Image im("./io_stuff/architecture/" ,"Detailed_Logical_View.pdf");
		im.set_height(6);
		im.set_width(12);
		ImageSet imset;
		imset.add_image(im);
		pres.add_slide(Slide(imset).set_title("Architecture - detailed logical view"));
	}
	{
		Image im("./io_stuff/" ,"webserver.pdf");
		im.set_height(6);
		im.set_width(9);
		ImageSet imset;
		imset.add_image(im);
		pres.add_slide(Slide(imset).set_title("Architecture - webserver"));
	}
	{
		Image im("./io_stuff/UseCaseDiagram/" ,"UseCaseDiagram.png");
		im.set_height(6);
		im.set_width(8);
		ImageSet imset;
		imset.add_image(im);
		pres.add_slide(Slide(imset).set_title("Architecture - use case diagram"));
	}
}

int main() {
	LatexPresentation pres("Visualization of algorithms in C++", "VisuAlgo");

	pres.author(R"=(Piotr Borowski\\Michał Niciejewski\\Krzysztof Małysa\\Philip Smolenski-Jensen)=");
	pres.footer_author("Dream Team");
	pres.date("10.06.2019");
	pres.institute("Uniwersytet Warszawski, Wydział Matematyki, Informatyki i Mechaniki");
	pres.footer_institute("MIMUW");

	add_diagrams(pres);
	// TODO: add some sensible slides :)

	cout << pres.to_str() << endl;
	return 0;
}
