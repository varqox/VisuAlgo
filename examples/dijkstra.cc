#include "../include/latex.h"
#include "../include/latex_presentation.h"
#include "../include/slide_builder.h"
#include "../include/undirected_graph.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace valgo;

LatexPresentation pres("Dijkstra", "Visualization of Dijkstra's Algorithm");
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
		visu_g.set_node_color(v, Color::GREEN);
		pres.add_slide(sb.build().set_title("Dijkstra"));

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
		visu_g.set_node_color(v, Color::LIGHT_GREEN);
		pres.add_slide(sb.build().set_title("Dijkstra"));
	}
	return dist;
}

int main() {
	sb.add_elem(visu_g);
	int n = 6;

	for (int i = 0; i < n; i++)
		visu_g.add_node(i, "dist=inf").set_node_color(i, Color::LIGHT_RED);

	vector<vector<pair<int, int>>> g(n);
	auto add_edge = [&](int a, int b, int c) {
		g[a].emplace_back(b, c);
		g[b].emplace_back(a, c);
		visu_g.add_edge(a, b, c);
	};
	add_edge(0, 1, 8);
	add_edge(0, 3, 7);
	add_edge(3, 4, 2);
	add_edge(0, 4, 10);
	add_edge(1, 4, 3);
	add_edge(4, 2, 3);
	add_edge(4, 5, 1);
	add_edge(5, 2, 1);

	dijkstra(n, g, 0);

	sb.remove_all_elements();

	pres.author("Dream team");
	pres.date("12.03.2019");
	pres.institute("MIMUW");
	cout << pres.to_str() << endl;
	return 0;
}