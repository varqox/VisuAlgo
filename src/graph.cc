#include "../include/latex.h"
#include "../include/latex_presentation.h"
#include "../include/slide_builder.h"
#include "../include/undirected_graph.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace valgo;

LatexPresentation pres("Graphs", "Visualization of graphs");
SlideBuilder sb;

int main() {
	UndirectedGraph<int, string, int> gg;
	sb.add_elem(gg);

	constexpr int init_level = 8;
	int level = init_level;
	for (int i = 1; i < level; i++)
		gg.add_edge(i, i * 2, i).add_edge(i, i * 2 + 1, i);
	gg.set_every_node_color(Color::LIGHT_YELLOW).set_every_edge_color(Color::BLUE);
	for (int i = level; i < level * 2; i++)
		gg.set_node_color(i, Color::LIGHT_RED).set_edge_color(i, i / 2, Color::LIGHT_RED);
	pres.add_slide(sb.build().set_title("grafy - hide\\_node"));
	while (level != 1) {
		for (int i = level; i < level * 2; i++)
			gg.hide_node(i);
		for (int i = level / 2; i < level; i++)
			gg.set_node_color(i, Color::LIGHT_RED).set_edge_color(i, i / 2, Color::LIGHT_RED);
		pres.add_slide(sb.build().set_title("grafy - hide\\_node"));
		level /= 2;
	}

	gg.remove_all_nodes();
	level = init_level;
	for (int i = 1; i < level; i++)
		gg.add_edge(i, i * 2, i).add_edge(i, i * 2 + 1, i);
	gg.set_every_node_color(Color::LIGHT_YELLOW).set_every_edge_color(Color::BLUE);
	for (int i = level; i < level * 2; i++)
		gg.set_node_color(i, Color::LIGHT_RED).set_edge_color(i, i / 2, Color::LIGHT_RED);
	pres.add_slide(sb.build().set_title("grafy - remove\\_node"));
	while (level != 1) {
		for (int i = level; i < level * 2; i++)
			gg.remove_node(i);
		for (int i = level / 2; i < level; i++)
			gg.set_node_color(i, Color::LIGHT_RED).set_edge_color(i, i / 2, Color::LIGHT_RED);
		pres.add_slide(sb.build().set_title("grafy - remove\\_node"));
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

	pres.add_slide(sb.build().set_title("grafy"));

	sb.remove_all_elements();


	pres.author("Dream team");
	pres.date("12.03.2019");
	pres.institute("MIMUW");
	cout << pres.to_str() << endl;
}
