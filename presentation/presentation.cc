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
#include "../include/geometry.h"
#include "../src/utilities.h"

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

void add_geometry(LatexPresentation& pres) {
	{
		SlideBuilder sb;
	
		Latex latex("\\begin{center}\\Large{Geometria}\\end{center}");
		sb.add_elem(latex);
		Latex latex2("\\begin{center}Przydatna do wizualizacji wielu algorytmów\\end{center}");
		sb.add_elem(latex2);

		pres.add_slide(sb.build().set_title("Geometria"));
		sb.remove_all_elements();
	}
	{
		SlideBuilder sb;
		Geometry geo;

		Point p(2, 4), p2(3, 3), p3(4, 2);
		p.set_color(Color::RED);
		p2.set_color(Color::GREEN);
		p3.set_color(Color::BLUE);

		geo.add(p).add(p2).add(p3);

		Line l(1, 1, 5, 5), l2(-3, 2, 3, -4);

		l.set_color(Color::MAGENTA).set_label("Magenta");
		l2.set_color(Color::CYAN).set_label("Cyan");
		
		geo.add(l).add(l2);

		sb.add_elem(geo);
		pres.add_slide(sb.build().set_title("Punkty i proste"));

		geo.set_coord_system(-6, 6, -6, 6);
		pres.add_slide(sb.build().set_title("Punkty i proste"));
	}
	{
		SlideBuilder sb;
		SourceCode sc;
		sc.set_lang("C++");
		sc.set_code(concat("Point p(2, 4), p2(3, 3), p3(4, 2);\n",
							"p.set_color(Color::RED);\n",
							"p2.set_color(Color::GREEN);\n",
							"p3.set_color(Color::BLUE);\n\n",

							"geo.add(p).add(p2).add(p3);\n\n",

							"Line l(1, 1, 5, 5), l2(-3, 2, 3, -4);\n\n",

							"l.set_color(Color::MAGENTA).set_label(\"Magenta\");\n",
							"l2.set_color(Color::CYAN).set_label(\"Cyan\");\n\n",
							
							"geo.add(l).add(l2);\n\n",

							"sb.add_elem(geo);\n",
							"geo.set_coord_system(-6, 6, -6, 6);\n",
							"pres.add_slide(sb.build().set_title(\"Punkty i proste\"));\n"));
		
		sb.add_elem(sc);
		pres.add_slide(sb.build().set_title("Kod źródłowy"));
	}
	{
		SlideBuilder sb;
		Geometry geo;
		sb.add_elem(geo);
		
		Rectangle r(-4, -2, 2, 2, "Rectangle");
		r.set_color(Color::RED);
		geo.add(r);

		Circle c(-2, -2.3, 2.5, "Circle");
		c.set_color(Color::GREEN);
		geo.add(c);

		Polygon pol;
		pol.add_vertex(3, -3).add_vertex(5, 4).add_vertex(3, 5).add_vertex(0, 3).add_vertex(1, 0);
		pol.set_color(Color::BLUE);
		pol.set_label("Pentagon");

		geo.add(pol);
		geo.set_coord_system(-6, 6, -6, 6);
		pres.add_slide(sb.build().set_title("Wielokąty"));
	}
	{
		SlideBuilder sb;
		Geometry geo;
		sb.add_elem(geo);

		Vector v(0, 0, 2, 0);
		v.set_color(Color::RED);
		Vector v1(0, 0, 0, 2);
		v1.set_color(Color::GREEN);
		Vector v2(0, 0, -2, 0);
		v2.set_color(Color::BLUE);
		Vector v3(0, 0, 0, -2);
		v3.set_color(Color::YELLOW);

		Vector v4(0, 0, 1.41, 1.41);
		v4.set_color(Color::MAGENTA);
		Vector v5(0, 0, 1.41, -1.41);
		v5.set_color(Color::CYAN);
		Vector v6(0, 0, -1.41, 1.41);
		v6.set_color(Color::LIGHT_BROWN);
		Vector v7(0, 0, -1.41, -1.41);
		v7.set_color(Color::LIGHT_RED);

		geo.add(v).add(v1).add(v2).add(v3).add(v4).add(v5).add(v6).add(v7);

		geo.set_coord_system(-3, 3, -3, 3);
		pres.add_slide(sb.build().set_title("Wektory"));
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
	// TODO: add some sensible slides :
	add_geometry(pres);

	cout << pres.to_str() << endl;
	return 0;
}
