#include "../include/array_1d.h"
#include "../include/array_2d.h"
#include "../include/block.h"
#include "../include/container.h"
#include "../include/directed_graph.h"
#include "../include/geometry.h"
#include "../include/image.h"
#include "../include/image_set.h"
#include "../include/itemize.h"
#include "../include/latex.h"
#include "../include/latex_presentation.h"
#include "../include/slide_builder.h"
#include "../include/source_code.h"
#include "../include/undirected_graph.h"
#include "../include/variable.h"
#include "../src/utilities.h"

#include <iostream>
#include <queue>
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
		Image im("./io_stuff/UseCaseDiagram/" ,"UseCaseDiagram.png");
		im.set_height(6);
		im.set_width(8);
		ImageSet imset;
		imset.add_image(im);
		pres.add_slide(Slide(imset).set_title("Architecture - use case diagram"));
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
		im.set_height(7.2);
		im.set_width(9.6);
		ImageSet imset;
		imset.add_image(im);
		pres.add_slide(Slide(imset).set_title("Architecture - webserver"));
	}
	{
		Itemize itemz;
		itemz.add_item(Latex("Webaplikacja"));
		itemz.add_item(Latex("Konwersja do kodu html"));
		itemz.add_item(Latex("Robienie grafów z użyciem tikza"));
		pres.add_slide(Slide(itemz).set_title("Dalsze możliwości rozwoju aplikacji"));
	}
}

template<class... Elems>
void add_column_view(Slide& slide, double ratio, const string& cpp_source_title, const string& cpp_source, Elems&&... elems) {
	// First column
	slide.add_elem(Latex(concat("\\begin{columns}[c]\n\\begin{column}{", to_string(ratio), "\\textwidth}\n")));
	slide.add_elem(Block(cpp_source_title, Color::LIGHT_BROWN, SourceCode().set_lang("C++").set_code(cpp_source)));

	// Second column
	slide.add_elem(Latex(concat("\\end{column}\n\\begin{column}{", to_string(1 - ratio), "\\textwidth}\n")));
	(slide.add_elem(std::forward<Elems>(elems)), ...);
	slide.add_elem(Latex("\\end{column}\n\\end{columns}\n"));
}

void add_containers(LatexPresentation& pres) {
	{
		SlideBuilder sb;

		Latex latex("\\begin{center}\\Large{Kontenery}\\end{center}");
		sb.add_elem(latex);
		Latex latex2("\\begin{center}Przydatne do wizualizacji wielu algorytmów\\end{center}");
		sb.add_elem(latex2);

		pres.add_slide(sb.build().set_title("Kontenery"));
		sb.remove_all_elements();
	}

	pres.add_section("Containers");
	Slide slide;

	add_column_view(slide, 0.8, "Containers - vector",
		"LatexPresentation pres(\"Title\",\n"
		"    \"footer title\");\n"
		"Container<std::vector<int>> vec = {1, 2, 3};\n"
		"vec.set_color(1, Color::GREEN);\n"
		"vec.emplace_back(4); slide.add_elem(vec);\n"
		"pres.add_slide(slide);\n", [] {
		Container<std::vector<int>> vec = {1, 2, 3};
		vec.set_color(1, Color::GREEN);
		vec.emplace_back(4);
		return vec;
	}());

	{
		Container<std::set<char>> set = {'a', 'b', 'c', 'd', 'e'};
		set.set_range_color(set.lower_bound('b'), set.upper_bound('d'), Color::RED);
		auto s1 = set;
		set.erase('c');
		auto s2 = set;
		set.emplace('c');
		auto s3 = set;

		add_column_view(slide, 0.67, "Containers - set",
			"Container<std::set<char>> set =\n"
			"    {'a', 'b', 'c', 'd', 'e'};\n"
			"set.set_range_color(set.lower_bound('b'),\n"
			"    set.upper_bound('d'), Color::RED);\n"
			"slide.add_elem(set);\n"
			"set.erase('c'); slide.add_elem(set);\n"
			"set.emplace('c');\n"
			"slide.add_elem(set);\n"
			"pres.add_slide(slide);\n",
			s1, s2, s3);
	}

	pres.add_slide(slide.set_title("Containers - vector \\& array").shrink(true));

	// Next slide
	{
		slide = {};
		Container<std::multimap<int, char>> mmap = {{4, 'a'}, {4, 'b'}, {5, 'a'}, {5, 'b'}};
		mmap.set_whole_color(Color::RED);
		auto m1 = mmap;
		auto i1 = ++mmap.begin();
		auto i2 = --mmap.end();
		mmap.set_range_color(i1, i2, Color::CYAN);
		auto m2 = mmap;
		auto x = *i1;
		mmap.erase(i1);
		auto m3 = mmap;
		mmap.emplace(x);
		auto m4 = mmap;

		add_column_view(slide, 0.58, "Containers - multimap",
			"LatexPresentation pres(\"Title\",\n"
			"    \"footer title\");\n"
			"Container<std::multimap<int, char>>\n"
			"    mmap = {{4, 'a'}, {4, 'b'},\n"
			"            {5, 'a'}, {5, 'b'}};\n"
			"mmap.set_whole_color(Color::RED);\n"
			"slide.add_elem(mmap);\n"
			"auto i1 = ++mmap.begin();\n"
			"auto i2 = ----mmap.end();\n"
			"mmap.set_range_color(i1, i2,\n"
			"                     Color::CYAN);\n"
			"slide.add_elem(mmap);\n"
			"auto x = *i1; mmap.erase(i1);\n"
			"slide.add_elem(mmap);\n"
			"mmap.emplace(x);\n"
			"slide.add_elem(mmap);\n"
			"pres.add_slide(slide);\n",
			m1, m2, m3, m4);

		pres.add_slide(slide.set_title("Containers - multimap").shrink(true));
	}

	// Next slide
	{
		slide = {};
		Itemize itemz;
		itemz.add_item(Latex("std::array"));
		itemz.add_item(Latex("std::vector"));
		itemz.add_item(Latex("std::deque"));
		itemz.add_item(Latex("std::forward\\_list"));
		itemz.add_item(Latex("std::list"));
		itemz.add_item(Latex("std::set"));
		itemz.add_item(Latex("std::map"));
		itemz.add_item(Latex("std::multiset"));
		itemz.add_item(Latex("std::multimap"));
		slide.add_elem(Latex("Supported STL containers:"));
		slide.add_elem(itemz);
		pres.add_slide(slide.set_title("Containers - support"));
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
		SourceCode sc;
		sc.set_lang("C++");
		sc.set_code(
			"SlideBuilder sb;\n"
			"Geometry geo;\n"
			"sb.add(geo);\n"
			"Point p(2, 4), p2(3, 3), p3(4, 2);\n"
			"p.set_color(Color::RED);\n"
			"p2.set_color(Color::GREEN);\n"
			"p3.set_color(Color::BLUE);\n"
			"\n"
			"geo.add(p).add(p2).add(p3);\n"
			"\n"
			"Line l(1, 1, 5, 5), l2(-3, 2, 3, -4);\n"
			"l.set_color(Color::MAGENTA).set_label(\"Magenta\");\n"
			"l2.set_color(Color::CYAN).set_label(\"Cyan\");\n"
			"geo.add(l).add(l2);\n"
			"sb.add_elem(geo);\n"
			"geo.set_coord_system(-6, 6, -6, 6);\n"
			"pres.add_slide(sb.build().set_title(\"Punkty i proste\"));\n");
		pres.add_slide(Slide(sc).set_title("Kod źródłowy").shrink(true));
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

void add_graphs(LatexPresentation& pres) {
	{
		SlideBuilder sb;

		Latex latex("\\begin{center}\\Large{Grafy}\\end{center}");
		sb.add_elem(latex);
		Latex latex2("\\begin{center}Przydatne do wizualizacji wielu algorytmów\\end{center}");
		sb.add_elem(latex2);

		pres.add_slide(sb.build().set_title("Grafy"));
		sb.remove_all_elements();
	}
	{
		SlideBuilder sb;
		DirectedGraph<int, string, int> g;
		sb.add_elem(g);
		g.add_edge(0, 1)
		 .add_edge(1, 0)
		 .add_edge(1, 2)
		 .add_edge(2, 3)
		 .add_edge(3, 4)
		 .add_edge(4, 5);
		pres.add_slide(sb.build().set_title("Grafy skierowane"));
		g.add_edge(5, 2);
		pres.add_slide(sb.build().set_title("Grafy skierowane - add\\_edge(5, 2)"));
		g.remove_edge(0, 1);
		pres.add_slide(sb.build().set_title("Grafy skierowane - remove\\_edge(0, 1)"));
		g.hide_edge(1, 2);
		pres.add_slide(sb.build().set_title("Grafy skierowane - hide\\_edge(1, 2)"));
		g.set_edge_color(2, 3, Color::GREEN);
		pres.add_slide(sb.build().set_title("Grafy skierowane - set\\_edge\\_color(2, 3, Color::GREEN)"));

		SourceCode code;
		code.set_lang("C++");
		code.set_code(
			R"=(SlideBuilder sb;)=" "\n"
			R"=(DirectedGraph<int, string, int> g;)=" "\n"
			R"=(sb.add_elem(g);)=" "\n"
			R"=(g.add_edge(0, 1))=" "\n"
			R"=( .add_edge(1, 0))=" "\n"
			R"=( .add_edge(1, 2))=" "\n"
			R"=( .add_edge(2, 3))=" "\n"
			R"=( .add_edge(3, 4))=" "\n"
			R"=( .add_edge(4, 5);)=" "\n" "\n"
			R"=(pres.add_slide(sb.build());)=" "\n"
			R"=(g.add_edge(5, 2);)=" "\n" "\n"
			R"=(pres.add_slide(sb.build());)=" "\n"
			R"=(g.remove_edge(0, 1);)=" "\n" "\n"
			R"=(pres.add_slide(sb.build());)=" "\n"
			R"=(g.hide_edge(1, 2);)=" "\n" "\n"
			R"=(pres.add_slide(sb.build());)=" "\n"
			R"=(g.set_edge_color(2, 3, Color::GREEN);)=" "\n"
			R"=(pres.add_slide(sb.build());)=");
		pres.add_slide(Slide(code).set_title("Grafy skierowane").shrink(true));
	}
	{
		SlideBuilder sb;
		UndirectedGraph<int, string, int> visu_g;
		sb.add_elem(visu_g);
		constexpr int n = 11;
		constexpr int source = 0;

		for (int i = 0; i < n; i++)
			visu_g.add_node(i, "dist=inf").set_node_color(i, Color::LIGHT_RED);

		vector<vector<int>> g(n);
		auto add_edge = [&](int a, int b) {
			g[a].emplace_back(b);
			g[b].emplace_back(a);
			visu_g.add_edge(a, b);
		};
		add_edge(0, 1);
		add_edge(0, 3);
		add_edge(3, 4);
		add_edge(0, 4);
		add_edge(1, 4);
		add_edge(4, 2);
		add_edge(4, 5);
		add_edge(5, 2);
		add_edge(1, 2);
		add_edge(3, 6);
		add_edge(3, 7);
		add_edge(3, 8);
		add_edge(8, 9);
		add_edge(7, 10);

		queue<int> q;
		vector<int> dist(n, -1);

		q.emplace(source);
		dist[source] = 0;
		visu_g.set_node_color(source, Color::LIGHT_YELLOW).set_node_info(source, "dist=0");
		int prev_dist = -1;
		while (!q.empty()) {
			auto top = q.front();
			q.pop();
			if (prev_dist != dist[top]) { // przechodzimy do nastepnego poziomu
				prev_dist = dist[top];
				pres.add_slide(sb.build().set_title("BFS"));
			}
			visu_g.set_node_color(top, Color::LIGHT_GREEN);
			for (auto&& neighbor : g[top]) {
				if (dist[neighbor] == -1) {
					dist[neighbor] = dist[top] + 1;
					visu_g.set_node_info(neighbor, "dist=" + to_string(dist[neighbor]));
					visu_g.set_node_color(neighbor, Color::LIGHT_YELLOW);
					q.emplace(neighbor);
				}
			}
		}
		pres.add_slide(sb.build().set_title("BFS"));

		SourceCode code;
		code.set_lang("C++");
		code.set_code(
			R"(SlideBuilder sb;)" "\n"
			R"(UndirectedGraph<int, string, int> visu_g;)" "\n"
			R"(sb.add_elem(visu_g);)" "\n"
			R"()" "\n"
			R"(for (int i = 0; i < n; i++))" "\n"
			R"(	visu_g.add_node(i, "dist=inf").set_node_color(i, Color::LIGHT_RED);)" "\n"
			R"()" "\n"
			R"(vector<vector<int>> g(n);)" "\n"
			R"(auto add_edge = [&](int a, int b) {)" "\n"
			R"(	g[a].emplace_back(b);)" "\n"
			R"(	g[b].emplace_back(a);)" "\n"
			R"(	visu_g.add_edge(a, b);)" "\n"
			R"(};)" "\n"
			R"(add_edge(1, 2);)" "\n"
			R"(// ...)");
		pres.add_slide(Slide(code).set_title("BFS").shrink(true));
		code.set_code(
			R"(q.emplace(source);)" "\n"
			R"(dist[source] = 0;)" "\n"
			R"(visu_g.set_node_color(source, Color::LIGHT_YELLOW).set_node_info(source, "dist=0");)" "\n"
			R"(int prev_dist = -1;)" "\n"
			R"(while (!q.empty()) {)" "\n"
			R"(	auto top = q.front();)" "\n"
			R"(	q.pop();)" "\n"
			R"(	if (prev_dist != dist[top]) { // przechodzimy do nastepnego poziomu)" "\n"
			R"(		prev_dist = dist[top];)" "\n"
			R"(		pres.add_slide(sb.build());)" "\n"
			R"(	})" "\n"
			R"(	visu_g.set_node_color(top, Color::LIGHT_GREEN);)" "\n"
			R"(	for (auto&& neighbor : g[top]) {)" "\n"
			R"(		if (dist[neighbor] == -1) {)" "\n"
			R"(			dist[neighbor] = dist[top] + 1;)" "\n"
			R"(			visu_g.set_node_info(neighbor, "dist=" + to_string(dist[neighbor]));)" "\n"
			R"(			visu_g.set_node_color(neighbor, Color::LIGHT_YELLOW);)" "\n"
			R"(			q.emplace(neighbor);)" "\n"
			R"(		})" "\n"
			R"(	})" "\n"
			R"(})" "\n"
			R"(pres.add_slide(sb.build());)");
		pres.add_slide(Slide(code).set_title("BFS").shrink(true));
	}
}

void add_arrays(LatexPresentation& pres) {
	{
		SlideBuilder sb;

		Latex latex("\\begin{center}\\Large{Tablice}\\end{center}");
		sb.add_elem(latex);
		Latex latex2("\\begin{center}Przydatne do wizualizacji wielu algorytmów\\end{center}");
		sb.add_elem(latex2);

		pres.add_slide(sb.build().set_title("Tablice"));
		sb.remove_all_elements();
	}
	{
		Array2D<int> arr("Array2D");
		arr.resize(5, 10);

		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 10; j++)
				arr.set_elem(i, j, 10 * (i + j) + i);

		arr.set_row_color(3, Color::LIGHT_BLUE);
		arr.set_column_color(4, Color::LIGHT_RED);
		arr.set_color(3, 4, Color::LIGHT_BROWN);

		SourceCode code;
		code.set_lang("C++").set_code(
			R"=(Array2D<int> arr("Array2D");)=" "\n"
			R"=(arr.resize(5, 10);)=" "\n"
			R"=()=" "\n"
			R"=(for (int i = 0; i < 5; i++))=" "\n"
			R"=(	for (int j = 0; j < 10; j++))=" "\n"
			R"=(		arr.set_elem(i, j, 10 * (i + j) + i);)=" "\n"
			R"=()=" "\n"
			R"=(arr.set_row_color(3, Color::LIGHT_BLUE);)=" "\n"
			R"=(arr.set_column_color(4, Color::LIGHT_RED);)=" "\n"
			R"=(arr.set_color(3, 4, Color::LIGHT_BROWN);)=" "\n"
			R"=()=" "\n"
			R"=(pres.add_slide(Slide(arr));)=");
		pres.add_slide(Slide(arr, code).set_title("Array2D").shrink(true));
	}
	{
		SlideBuilder sb;
		constexpr int N = 12;
		Array1D<bool> vtab("pierwsza");
		Variable<int> wielo("wykreślmy wielokrotności");
		Variable<int> wykr("teraz wykreśliliśmy");

		sb.add_elem(vtab);

		vtab.resize(N);
		for (int i = 2; i < N; i++)
			vtab.set_elem(i, true);

		vector<bool> is_prime(N, true);
		is_prime[0] = is_prime[1] = false;

		vtab.set_color(0, Color::LIGHT_RED).set_color(1, Color::LIGHT_RED);
		pres.add_slide(sb.build().set_title("Sieve of Erathostenes"));

		sb.add_elem(wielo);

		for (int i = 2; i < N; ++i) {
			if (is_prime[i]) {
				wielo.set(i);
				vtab.set_color(i, Color::LIGHT_YELLOW);
				pres.add_slide(sb.build().set_title("Sieve of Erathostenes"));
				for (int j = i + i; j < N; j += i) {
					sb.add_elem(wykr);
					wykr.set(j);
					is_prime[j] = false;
					vtab.set_color(j, Color::LIGHT_RED).set_elem(j, false);
					pres.add_slide(sb.build().set_title("Sieve of Erathostenes"));
					sb.remove_elem(wykr);
				}
			}
		}

		sb.remove_all_elements();

		SourceCode code;
		code.set_lang("C++");
		code.set_code(
			R"(SlideBuilder sb;)" "\n"
			R"(constexpr int N = 12;)" "\n"
			R"(Array1D<bool> vtab("pierwsza");)" "\n"
			R"(Variable<int> wielo("wykreslmy wielokrotnosci");)" "\n"
			R"(Variable<int> wykr("teraz wykreslilismy");)" "\n"
			R"()" "\n"
			R"(sb.add_elem(vtab);)" "\n"
			R"()" "\n"
			R"(vtab.resize(N);)" "\n"
			R"(for (int i = 2; i < N; i++))" "\n"
			R"(	vtab.set_elem(i, true);)" "\n"
			R"()" "\n"
			R"(vector<bool> is_prime(N, true);)" "\n"
			R"(is_prime[0] = is_prime[1] = false;)" "\n"
			R"()" "\n"
			R"(vtab.set_color(0, Color::LIGHT_RED).set_color(1, Color::LIGHT_RED);)" "\n"
			R"(pres.add_slide(sb.build());)" "\n"
			R"()" "\n"
			R"(sb.add_elem(wielo);)");
		pres.add_slide(Slide(code).set_title("Sieve of Erathostenes").shrink(true));
		code.set_code(
			R"(for (int i = 2; i < N; ++i) {)" "\n"
			R"(	if (is_prime[i]) {)" "\n"
			R"(		wielo.set(i);)" "\n"
			R"(		vtab.set_color(i, Color::LIGHT_YELLOW);)" "\n"
			R"(		pres.add_slide(sb.build());)" "\n"
			R"(		for (int j = i + i; j < N; j += i) {)" "\n"
			R"(			sb.add_elem(wykr);)" "\n"
			R"(			wykr.set(j);)" "\n"
			R"(			is_prime[j] = false;)" "\n"
			R"(			vtab.set_color(j, Color::LIGHT_RED).set_elem(j, false);)" "\n"
			R"(			pres.add_slide(sb.build());)" "\n"
			R"(			sb.remove_elem(wykr);)" "\n"
			R"(		})" "\n"
			R"(	})" "\n"
			R"(})");
		pres.add_slide(Slide(code).set_title("Sieve of Erathostenes").shrink(true));
	}
}

int main() {
	LatexPresentation pres("Visualization of algorithms in C++", "VisuAlgo");

	pres.author(R"=(
		\text{Piotr Borowski}
		\and
		\text{Michał Niciejewski}
		\and
		\text{Krzysztof Małysa}
		\and
		\text{Philip Smolenski-Jensen}
		)=");
	pres.footer_author("Dream Team");
	pres.date("10.06.2019");
	pres.institute("Uniwersytet Warszawski, Wydział Matematyki, Informatyki i Mechaniki");
	pres.footer_institute("MIMUW");

	add_diagrams(pres);
	add_containers(pres);
	add_geometry(pres);
	add_arrays(pres);
	add_graphs(pres);

	cout << pres.to_str() << endl;
	return 0;
}
