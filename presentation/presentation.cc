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
#include "../include/itemize.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace valgo;

void add_diagrams(LatexPresentation& pres) {
	{
		Itemize itemz;
		itemz.add_item(Latex("nauczyciel informatyki prezentujący działanie algorytmu sortowania"));
		itemz.add_item(Latex("organizator konkursu algorytmicznego tworzący omówienie zadań"));
		itemz.add_item(Latex("osoba tworząca internetowy kurs STLa"));
		itemz.add_item(Latex("pracownik naukowy publikujący własny algorytm"));
		pres.add_slide(Slide(itemz).set_title("Grupy użytkowników / Role w systemie"));
	}
	{
		Itemize itemz;
		itemz.add_item(Latex("Tablice 1D, Tablice 2D"));
		itemz.add_item(Latex("Inline LaTeX, zmienne, kod źródłowy"));
		itemz.add_item(Latex("Grafy (nieskierowane, skierowane, dagi, drzewa, grafy funkcyjne)"));
		itemz.add_item(Latex("Kontenery"));
		itemz.add_item(Latex("Macierze"));
		itemz.add_item(Latex("Geometria"));
		itemz.add_item(Latex("Obrazki"));
		pres.add_slide(Slide(itemz).set_title("Funkcjonalności"));
	}
	{
		Itemize itemz;
		itemz.add_item(Latex("C++"));
		itemz.add_item(Latex("Graphviz"));
		itemz.add_item(Latex("Github"));
		itemz.add_item(Latex("GoogleTest"));
		itemz.add_item(Latex("Doxygen"));
		itemz.add_item(Latex("LaTeX"));
		pres.add_slide(Slide(itemz).set_title("Narzędzia i technologie"));
	}
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
	{
		Itemize itemz;
		itemz.add_item(Latex("Webaplikacja"));
		itemz.add_item(Latex("Konwersja do kodu html"));
		itemz.add_item(Latex("Robienie grafów z użyciem tikza"));
		pres.add_slide(Slide(itemz).set_title("Dalsze możliwości rozwoju aplikacji"));
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
