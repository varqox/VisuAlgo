#include "../include/undirected_graph.h"
#include "../include/array_1d.h"

#include <gtest/gtest.h>

using namespace valgo;

TEST (UndirectedGraph, draw_as_latex) {
	UndirectedGraph<int, int, int> x;
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
}

TEST (UndirectedGraph, draw_as_html) {
	UndirectedGraph<int, int, int> x;
	EXPECT_THROW(Array1D<int>().draw_as_html(), NotImplemented);
}

TEST (UndirectedGraph, clone) {
	UndirectedGraph<int, int, int> x;
	x.add_edge(1, 2)
	 .add_edge(2, 3)
	 .add_edge(3, 4)
	 .add_edge(4, 5)
	 .add_edge(5, 6)
	 .hide_edge(1, 2)
	 .hide_node(6)
	 .set_edge_color(2, 3, Color::RED)
	 .set_node_color(4, Color::GREEN)
	 .set_edge_info(3, 4, 42)
	 .set_node_info(5, 43);
	EXPECT_EQ(x.clone()->draw_as_latex(), x.draw_as_latex());
}

TEST (UndirectedGraph, add_node) {
	UndirectedGraph<int, int, int> x;
	x.add_node(1, 5)
	 .add_node(2)
	 .add_node(51)
	 .add_node(-50, 42)
	 .add_node(1 << 30)
	 .add_node(1);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" -50 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">-50</td></tr><hr/><tr><td width=\"50\">42</td></tr></table>>];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">1</td></tr></table>>];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">2</td></tr></table>>];\n"
		" 51 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">51</td></tr></table>>];\n"
		" 1073741824 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">1073741824</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
}

TEST (UndirectedGraph, add_edge) {
	UndirectedGraph<int, int, int> x;
	x.add_edge(1, 2, 42)
	 .add_edge(2, 1)
	 .add_edge(2, 3)
	 .add_edge(1, 2, 37);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" 1 -> 2 [label=\"37\"];\n"
		" 2 -> 3 [];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">1</td></tr></table>>];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">2</td></tr></table>>];\n"
		" 3 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">3</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
}

TEST (UndirectedGraph, remove_node) {
	UndirectedGraph<int, int, int> x;
	x.add_node(1)
	 .add_node(2)
	 .add_node(51)
	 .remove_node(1);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">2</td></tr></table>>];\n"
		" 51 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">51</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
	x.remove_node(3);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">2</td></tr></table>>];\n"
		" 51 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">51</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
	x.remove_node(2)
	 .remove_node(51);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
}

TEST (UndirectedGraph, remove_edge) {
	UndirectedGraph<int, int, int> x;
	x.add_edge(1, 2)
	 .add_edge(2, 1)
	 .add_edge(2, 3)
	 .remove_edge(1, 2);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" 2 -> 3 [];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">1</td></tr></table>>];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">2</td></tr></table>>];\n"
		" 3 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">3</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
	x.remove_edge(1, 2);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" 2 -> 3 [];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">1</td></tr></table>>];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">2</td></tr></table>>];\n"
		" 3 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">3</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
	x.remove_edge(2, 1)
	 .remove_edge(2, 3);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">1</td></tr></table>>];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">2</td></tr></table>>];\n"
		" 3 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">3</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
}

TEST (UndirectedGraph, remove_all_nodes) {
	UndirectedGraph<int, int, int> x;
	x.add_node(1)
	 .add_node(2)
	 .add_edge(1, 2)
	 .add_node(51)
	 .remove_all_nodes();
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
	x.add_node(1);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">1</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
}

TEST (UndirectedGraph, remove_all_edges) {
	UndirectedGraph<int, int, int> x;
	x.add_edge(1, 2)
	 .add_edge(2, 1)
	 .add_edge(2, 3)
	 .remove_all_edges();
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">1</td></tr></table>>];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">2</td></tr></table>>];\n"
		" 3 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">3</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
}

TEST (UndirectedGraph, set_node_info) {
	UndirectedGraph<int, int, int> x;
	x.add_node(1, 5)
	 .set_node_info(1, 3)
	 .add_node(2)
	 .set_node_info(2, 7)
	 .set_node_info(3, 42);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">1</td></tr><hr/><tr><td width=\"50\">3</td></tr></table>>];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">2</td></tr><hr/><tr><td width=\"50\">7</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
}

TEST (UndirectedGraph, set_edge_info) {
	UndirectedGraph<int, int, int> x;
	x.add_edge(1, 2, 42)
	 .add_edge(2, 3)
	 .set_edge_info(1, 2, 37)
	 .set_edge_info(2, 1, 32)
	 .set_edge_info(5, 6, 7);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" 1 -> 2 [label=\"32\"];\n"
		" 2 -> 3 [];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">1</td></tr></table>>];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">2</td></tr></table>>];\n"
		" 3 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">3</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
}

TEST (UndirectedGraph, set_node_color) {
	UndirectedGraph<int, int, int> x;
	x.add_node(1)
	 .set_node_color(1, Color::RED)
	 .add_node(2)
	 .set_node_color(2, Color::GREEN);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"#FF0000\"><tr><td width=\"50\">1</td></tr></table>>];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"#00FF00\"><tr><td width=\"50\">2</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
	x.set_node_color(1, std::nullopt)
	 .set_node_color(2, Color::YELLOW);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">1</td></tr></table>>];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"#FFFF00\"><tr><td width=\"50\">2</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
}

TEST (UndirectedGraph, set_every_node_color) {
	UndirectedGraph<int, int, int> x;
	x.add_node(1, 5)
	 .add_node(2)
	 .add_node(-50, 42)
	 .set_every_node_color(Color::RED);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" -50 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"#FF0000\"><tr><td width=\"50\">-50</td></tr><hr/><tr><td width=\"50\">42</td></tr></table>>];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"#FF0000\"><tr><td width=\"50\">1</td></tr><hr/><tr><td width=\"50\">5</td></tr></table>>];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"#FF0000\"><tr><td width=\"50\">2</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
	x.set_every_node_color(Color::GREEN);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" -50 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"#00FF00\"><tr><td width=\"50\">-50</td></tr><hr/><tr><td width=\"50\">42</td></tr></table>>];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"#00FF00\"><tr><td width=\"50\">1</td></tr><hr/><tr><td width=\"50\">5</td></tr></table>>];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"#00FF00\"><tr><td width=\"50\">2</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
	x.set_every_node_color(std::nullopt);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" -50 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">-50</td></tr><hr/><tr><td width=\"50\">42</td></tr></table>>];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">1</td></tr><hr/><tr><td width=\"50\">5</td></tr></table>>];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">2</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
}

TEST (UndirectedGraph, set_edge_color) {
	UndirectedGraph<int, int, int> x;
	x.add_edge(1, 2, 42)
	 .add_edge(2, 1)
	 .add_edge(2, 3)
	 .set_edge_color(1, 2, Color::RED)
	 .set_edge_color(2, 3, Color::GREEN)
	 .set_edge_color(5, 6, Color::BLUE);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" 1 -> 2 [color=\"#FF0000\"];\n"
		" 2 -> 3 [color=\"#00FF00\"];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">1</td></tr></table>>];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">2</td></tr></table>>];\n"
		" 3 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">3</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
	x.set_edge_color(1, 2, Color::YELLOW)
	 .set_edge_color(2, 3, std::nullopt);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" 1 -> 2 [color=\"#FFFF00\"];\n"
		" 2 -> 3 [];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">1</td></tr></table>>];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">2</td></tr></table>>];\n"
		" 3 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">3</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
}

TEST (UndirectedGraph, set_every_edge_color) {
	UndirectedGraph<int, int, int> x;
	x.add_edge(1, 2)
	 .set_edge_color(1, 2, Color::RED)
	 .add_edge(2, 1)
	 .add_edge(2, 3)
	 .set_every_edge_color(Color::GREEN);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" 1 -> 2 [color=\"#00FF00\"];\n"
		" 2 -> 3 [color=\"#00FF00\"];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">1</td></tr></table>>];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">2</td></tr></table>>];\n"
		" 3 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">3</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
	x.set_every_edge_color(std::nullopt);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" 1 -> 2 [];\n"
		" 2 -> 3 [];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">1</td></tr></table>>];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">2</td></tr></table>>];\n"
		" 3 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">3</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
}

TEST (UndirectedGraph, hide_node) {
	UndirectedGraph<int, int, int> x;
	x.add_node(1)
	 .add_node(2)
	 .add_node(51)
	 .hide_node(1);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">1</td></tr></table>>, style=invis];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">2</td></tr></table>>];\n"
		" 51 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">51</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
	x.hide_node(3);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">1</td></tr></table>>, style=invis];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">2</td></tr></table>>];\n"
		" 51 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">51</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
	x.hide_node(2)
	 .hide_node(51);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">1</td></tr></table>>, style=invis];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">2</td></tr></table>>, style=invis];\n"
		" 51 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">51</td></tr></table>>, style=invis];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
}

TEST (UndirectedGraph, hide_edge) {
	UndirectedGraph<int, int, int> x;
	x.add_edge(1, 2)
	 .add_edge(2, 1)
	 .add_edge(2, 3)
	 .hide_edge(1, 2);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" 1 -> 2 [style=invis];\n"
		" 2 -> 3 [];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">1</td></tr></table>>];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">2</td></tr></table>>];\n"
		" 3 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">3</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
	x.hide_edge(1, 2);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" 1 -> 2 [style=invis];\n"
		" 2 -> 3 [];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">1</td></tr></table>>];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">2</td></tr></table>>];\n"
		" 3 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">3</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
	x.hide_edge(2, 1)
	 .hide_edge(2, 3);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" 1 -> 2 [style=invis];\n"
		" 2 -> 3 [style=invis];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">1</td></tr></table>>];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">2</td></tr></table>>];\n"
		" 3 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">3</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
}

TEST (UndirectedGraph, unhide_node) {
	UndirectedGraph<int, int, int> x;
	x.add_node(1)
	 .hide_node(1)
	 .unhide_node(1);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">1</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
}

TEST (UndirectedGraph, unhide_edge) {
	UndirectedGraph<int, int, int> x;
	x.add_edge(1, 2)
	 .add_edge(2, 1)
	 .add_edge(2, 3)
	 .hide_edge(1, 2)
	 .hide_edge(2, 1)
	 .unhide_edge(1, 2);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" 1 -> 2 [];\n"
		" 2 -> 3 [];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">1</td></tr></table>>];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">2</td></tr></table>>];\n"
		" 3 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">3</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
	x.unhide_edge(2, 1);
	EXPECT_EQ(x.draw_as_latex(), "\\begin{figure}\n"
		"\\begin{graphviz}{neato}\n"
		"digraph {\n"
		" ratio=\"fill\";\n"
		" margin=\"0\";\n"
		" outputorder=\"edgesfirst\";\n"
		" overlap=false;\n"
		" splines = true;\n"
		" sep=\"+15,15\"\n"
		" size=\"8,4.8\";\n"
		" graph [fontname = \"Monospace\"];\n"
		" node [fontname = \"Monospace\", shape=plain, fontsize=11];\n"
		" edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n"
		" 1 -> 2 [];\n"
		" 2 -> 3 [];\n"
		" 1 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">1</td></tr></table>>];\n"
		" 2 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">2</td></tr></table>>];\n"
		" 3 [label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\" bgcolor=\"white\"><tr><td width=\"50\">3</td></tr></table>>];\n"
		"}\n"
		"\\end{graphviz}\n"
		"\\end{figure}");
}
