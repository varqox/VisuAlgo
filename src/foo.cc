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

LatexPresentation pres("Test", "Test presentation");
SlideBuilder sb;
UndirectedGraph<int, string, int> visu_g;

vector<int> dijkstra(int n, const vector<vector<pair<int, int>>> &g, int source) {
	vector<int> dist(n, 1e9);
	dist[source] = 0;
	visu_g.set_node_color(source, Color::LIGHT_YELLOW).set_node_info(source, "dist=0");

	set<pair<int, int>> s = { {0, source} };

	while (!s.empty()) {
		int v = s.begin()->second;
		s.erase(s.begin());
		visu_g.set_node_color(v, Color::LIGHT_GREEN);
		pres.add_slide(sb.build());

		for (auto&& neighbor : g[v]) {
			int u = neighbor.first, w = neighbor.second;

			if (dist[u] > dist[v] + w) {
				auto it = s.find({dist[u], u});
				if (it != s.end())
					s.erase(it);
				dist[u] = dist[v] + w;
				visu_g.set_node_info(u, "dist=" + to_string(dist[u]));
				visu_g.set_node_color(u, Color::LIGHT_YELLOW);
				s.emplace(dist[u], u);
			}
		}
		pres.add_slide(sb.build());
	}
	return dist;
}

int main() {
	sb.add_elem(visu_g);
	int n, m;
	cin >> n >> m;

	for (int i = 0; i < n; i++)
		visu_g.add_node(i, "dist=inf").set_node_color(i, Color::LIGHT_RED);

	vector<vector<pair<int, int>>> g(n);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		g[a].emplace_back(b, c);
		g[b].emplace_back(a, c);
		visu_g.add_edge(a, b, c);
	}

	dijkstra(n, g, 0);

	sb.remove_all_elements();

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
			Block("Standardowa implementacja", Color::LIGHT_BROWN,
				Latex("\\LaTeX~is coming..."), code));

		Itemize itmz;
		itmz.add_item(Latex("Znajduje liczby pierwsze od 2 do $N - 1$"));
		itmz.add_item(Latex("Działa w $O(n \\lg n)$"));
		slide.add_elem(itmz);

		pres.add_slide(slide);
	}

	constexpr int N = 12;
	Array1D<bool> vtab("pierwsza");
	sb.add_elem(vtab);
	vtab.resize(N);

	vector<bool> is_prime(N, true);
	is_prime[0] = is_prime[1] = false;
	vtab.set_color(0, Color::LIGHT_RED);
	vtab.set_color(1, Color::LIGHT_RED);
	pres.add_slide(sb.build());
	Variable<int> wyk("wykreślmy wielokrotności");
	sb.add_elem(wyk);

	for (int i = 2; i < N; ++i) {
		if (is_prime[i]) {
			wyk.set(i);
			vtab.set_color(i, Color::LIGHT_YELLOW);
			pres.add_slide(sb.build());
			for (int j = i + i; j < N; j += i) {
				Variable<int> wyk2("teraz wykreśliliśmy");
				wyk2.set(j);
				sb.add_elem(wyk2);
				is_prime[j] = false;
				vtab.set_color(j, Color::LIGHT_RED);
				vtab.set_elem(j, false);
				pres.add_slide(sb.build());
				sb.remove_elem(wyk2);
			}
		}
	}

	sb.remove_all_elements();

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
	   .set_color(4, Color::LIGHT_GREEN)
	   .set_color(2, Color::LIGHT_BLUE)
	   .set_color(7, Color::LIGHT_RED)
	   .set_color(1, Color::LIGHT_YELLOW)
	   .set_color(3, Color::LIGHT_BROWN);

	Array1D<int> arr2;
	sb.add_elem(arr2);
	arr2.set(vec)
	    .set_whole_array_color(Color::LIGHT_YELLOW)
	    .set_range_color(2, 4, Color::LIGHT_BROWN)
	    .set_range_color(5, 6, std::nullopt);

	Variable<double> var("pi");
	var.set(3.14159265);
	sb.add_elem(var);

	pres.add_slide(sb.build());

	Array2D<int> arr3("Kuchar");
		arr3.resize (5, 10);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			arr3.set_elem(i, j, 10 * (i + j) + i);
		}
	}
	arr3.set_row_color(3, Color::LIGHT_BLUE);
	arr3.set_column_color(4, Color::LIGHT_RED);
	arr3.set_color(3, 4, Color::LIGHT_BROWN);

	sb.add_elem(arr3);
	pres.add_slide(sb.build());

	sb.remove_all_elements();
	UndirectedGraph<int, string, int> gg;
	sb.add_elem(gg);

	constexpr int init_level = 8;
	int level = init_level;
	for (int i = 1; i < level; i++)
		gg.add_edge(i, i * 2, i).add_edge(i, i * 2 + 1, i);
	gg.set_every_node_color(Color::LIGHT_YELLOW).set_every_edge_color(Color::BLUE);
	for (int i = level; i < level * 2; i++)
		gg.set_node_color(i, Color::LIGHT_RED).set_edge_color(i, i / 2, Color::LIGHT_RED);
	pres.add_slide(sb.build().set_title("hide\\_node"));
	while (level != 1) {
		for (int i = level; i < level * 2; i++)
			gg.hide_node(i);
		for (int i = level / 2; i < level; i++)
			gg.set_node_color(i, Color::LIGHT_RED).set_edge_color(i, i / 2, Color::LIGHT_RED);
		pres.add_slide(sb.build().set_title("hide\\_node"));
		level /= 2;
	}

	gg.remove_all_nodes();
	level = init_level;
	for (int i = 1; i < level; i++)
		gg.add_edge(i, i * 2, i).add_edge(i, i * 2 + 1, i);
	gg.set_every_node_color(Color::LIGHT_YELLOW).set_every_edge_color(Color::BLUE);
	for (int i = level; i < level * 2; i++)
		gg.set_node_color(i, Color::LIGHT_RED).set_edge_color(i, i / 2, Color::LIGHT_RED);
	pres.add_slide(sb.build().set_title("remove\\_node"));
	while (level != 1) {
		for (int i = level; i < level * 2; i++)
			gg.remove_node(i);
		for (int i = level / 2; i < level; i++)
			gg.set_node_color(i, Color::LIGHT_RED).set_edge_color(i, i / 2, Color::LIGHT_RED);
		pres.add_slide(sb.build().set_title("remove\\_node"));
		level /= 2;
	}

	sb.remove_all_elements();
	UndirectedGraph<int, string, int> h;
	sb.add_elem(h);

	h.add_edge(1, 2)
	 .add_edge(3, 2)
	 .add_edge(2, 4)
	 .add_edge(4, 5)
	 .add_edge(4, 6)
	 .add_edge(4, 7)
	 .add_edge(10, 5)
	 .add_edge(9, 6)
	 .add_edge(9, 8)
	 .add_edge(3, 8)
	 .add_edge(3, 9)
	 .add_edge(2, 10)
	 .add_edge(10, 11)
	 .add_edge(11, 11)
	 .set_node_color(1, Color::RED)
	 .set_node_color(2, Color::GREEN)
	 .set_node_color(3, Color::LIGHT_BLUE)
	 .set_node_color(4, Color::YELLOW)
	 .set_node_color(5, Color::LIGHT_BROWN)
	 .set_node_color(6, Color::RED)
	 .set_node_color(7, Color::GREEN)
	 .set_node_color(8, Color::LIGHT_BLUE)
	 .set_node_color(9, Color::YELLOW)
	 .set_node_color(10, Color::LIGHT_BROWN)
	 .set_node_color(11, Color::RED)
	 .set_node_info(1, "hejka1\\nxxx")
	 .set_node_info(2, "hejka2\\nxxx")
	 .set_node_info(3, "hejka3\\nxxx")
	 .set_node_info(4, "hejka4\\nxxx")
	 .set_node_info(5, "hejka5\\nxxx")
	 .set_node_info(6, "hejka6\\nxxx")
	 .set_node_info(7, "hejka7\\nxxx")
	 .set_node_info(8, "hejka8\\nxxx")
	 .set_node_info(9, "hejka9\\nxxx")
	 .set_node_info(10, "hejka10\\nxxx")
	 .set_node_info(11, "hejka11\\nxxx");

	pres.add_slide(sb.build());

	sb.remove_all_elements();

	int sz = 4;
	Array1D<int> bins("binsearch");
	Variable<int> szukamy("szukamy");
	Variable<int> lewy("lewy");
	Variable<int> prawy("prawy");
	sb.add_elem(bins);
	sb.add_elem(szukamy);
	sb.add_elem(lewy);
	sb.add_elem(prawy);

	vector<int> b = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	bins.resize(11);
	for (size_t i = 0; i < b.size(); i++)
		bins.set_elem(i, b[i]);

	szukamy.set(sz);

	int l = 0, r = b.size() - 1;
	while (l < r) {
		lewy.set(l);
		prawy.set(r);
		int mid = (l + r + 1) / 2;
		bins.set_whole_array_color(std::nullopt);
		bins.set_range_color(l, r, Color::LIGHT_GREEN);
		pres.add_slide(sb.build());
		bins.set_color(mid, Color::LIGHT_YELLOW);
		pres.add_slide(sb.build());
		if (b[mid] <= sz) {
			l = mid;
		}
		else {
			r = mid - 1;
		}
	}

	lewy.set(l);
	prawy.set(r);
	int mid = (l + r + 1) / 2;
	bins.set_whole_array_color(std::nullopt);
	bins.set_range_color(l, r, Color::LIGHT_GREEN);
	pres.add_slide(sb.build());
	bins.set_color(mid, Color::LIGHT_YELLOW);
	pres.add_slide(sb.build());

	pres.author("Dream team");
	pres.date("12.03.2019");
	pres.institute("MIMUW");
	cout << pres.to_str() << endl;
}
/*
6 8
0 1 8
0 3 7
3 4 2
0 4 10
1 4 3
4 2 3
4 5 1
5 2 1
*/
