#pragma once

#include "directed_graph.h"

#include <queue>
#include <iostream>
using namespace std;

namespace valgo {

enum class FuncGraphView {
	sparse,
	list
};

template<class NodeId, class NodeInfo, class EdgeInfo>
class FuncGraph : public DirectedGraph<NodeId, NodeInfo, EdgeInfo> {
public:
protected:
	virtual std::string tool_name() const override;

	FuncGraphView view_;

	using DirectedGraph<NodeId, NodeInfo, EdgeInfo>::edges_;
	using DirectedGraph<NodeId, NodeInfo, EdgeInfo>::nodes_;
	using typename DirectedGraph<NodeId, NodeInfo, EdgeInfo>::Node;
	using typename DirectedGraph<NodeId, NodeInfo, EdgeInfo>::Edge;

	using typename DirectedGraph<NodeId, NodeInfo, EdgeInfo>::NodesIterator;
	using typename DirectedGraph<NodeId, NodeInfo, EdgeInfo>::NodesConstIterator;
	using typename DirectedGraph<NodeId, NodeInfo, EdgeInfo>::EdgesIterator;
	using typename DirectedGraph<NodeId, NodeInfo, EdgeInfo>::EdgesConstIterator;

	using DirectedGraph<NodeId, NodeInfo, EdgeInfo>::find_edge;

	// (found cycle, may add to result)
	std::pair<bool, bool> find_cycle(const Node* st, std::set<const Node*>& vis, std::set<const Node*>& on_stack,
		std::vector<const Node*>& result) const;

	// Returns pointers to nodes in bfs order.
	std::vector<std::vector<const Node*>> find_all_cycles() const;

public:
	FuncGraph(FuncGraphView view = FuncGraphView::sparse) : view_(view) {}

	FuncGraph& set_view(FuncGraphView view) {
		view_ = view;
		return *this;
	}

	virtual std::unique_ptr<SlideElement> clone() const override;

	virtual DotCode draw_as_dot() const override;

	// fixing chaining
	virtual FuncGraph& add_node(const NodeId& node, std::optional<NodeInfo> node_info = std::nullopt) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::add_node(node, node_info), *this;
	}
	virtual FuncGraph& add_edge(const NodeId& from, const NodeId& to,
			std::optional<EdgeInfo> edge_info = std::nullopt) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::add_edge(from, to, edge_info), *this;
	}
	virtual FuncGraph& set_node_info(const NodeId& node, std::optional<NodeInfo> node_info) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::set_node_info(node, node_info), *this;
	}
	virtual FuncGraph& set_edge_info(const NodeId& from, const NodeId& to, std::optional<EdgeInfo> edge_info) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::set_edge_info(from, to, edge_info), *this;
	}
	virtual FuncGraph& set_node_color(const NodeId& node, std::optional<Color> color) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::set_node_color(node, color), *this;
	}
	virtual FuncGraph& set_every_node_color(const std::optional<Color>& color) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::set_every_node_color(color), *this;
	}
	virtual FuncGraph& set_edge_color(const NodeId& from, const NodeId& to, std::optional<Color> color) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::set_edge_color(from, to, color), *this;
	}
	virtual FuncGraph& set_every_edge_color(const std::optional<Color>& color) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::set_every_edge_color(color), *this;
	}
	virtual FuncGraph& hide_node(const NodeId& node) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::hide_node(node), *this;
	}
	virtual FuncGraph& hide_edge(const NodeId& from, const NodeId& to) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::hide_edge(from, to), *this;
	}
	virtual FuncGraph& unhide_node(const NodeId& node) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::unhide_node(node), *this;
	}
	virtual FuncGraph& unhide_edge(const NodeId& from, const NodeId& to) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::unhide_edge(from, to), *this;
	}
	virtual FuncGraph& remove_node(const NodeId& node) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::remove_node(node), *this;
	}
	virtual FuncGraph& remove_all_nodes() override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::remove_all_nodes(), *this;
	}
	virtual FuncGraph& remove_edge(const NodeId& from, const NodeId& to) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::remove_edge(from, to), *this;
	}
	virtual FuncGraph& remove_all_edges() override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::remove_all_edges(), *this;
	}
};

/****************** Implementation ******************/

template<class NodeId, class NodeInfo, class EdgeInfo>
inline std::string FuncGraph<NodeId, NodeInfo, EdgeInfo>::tool_name() const {
	return view_ == FuncGraphView::sparse ? "neato" : "dot";
}

template<class NodeId, class NodeInfo, class EdgeInfo>
std::pair<bool, bool> FuncGraph<NodeId, NodeInfo, EdgeInfo>::find_cycle(const Node* st, std::set<const Node*>& vis,
		std::set<const Node*>& on_stack, std::vector<const Node*>& result) const {
	vis.emplace(st);
	on_stack.emplace(st);
	for (auto& nei_id : st->nei_) {
		auto nei_ptr = &nodes_.find(nei_id)->second;
		if (vis.find(nei_ptr) == vis.end()) {
			auto [found, may] = find_cycle(nei_ptr, vis, on_stack, result);
			if (found) {
				if (may) {
					if (st != result[0])
						result.emplace_back(st);
					else
						may = false;
				}
				return {true, may};
			}
		}
		else if (on_stack.find(nei_ptr) != on_stack.end()) {
			result.emplace_back(nei_ptr);
			if (nei_ptr == st)
				return {true, false};
			result.emplace_back(st);
			return {true, true};
		}
	}
	on_stack.erase(st);
	return {false, false};
}

template<class NodeId, class NodeInfo, class EdgeInfo>
std::vector<std::vector<const typename FuncGraph<NodeId, NodeInfo, EdgeInfo>::Node*>>
FuncGraph<NodeId, NodeInfo, EdgeInfo>::find_all_cycles() const {
	std::set<const Node*> vis;
	std::vector<std::vector<const Node*>> ret;

	// Start looking for cycles from all nodes.
	for (auto& [id, node] : nodes_) {
		if (vis.find(&node) == vis.end()) {
			std::vector<const Node*> curr_list;
			std::set<const Node*> curr_stack;
			auto [found, may] = find_cycle(&node, vis, curr_stack, curr_list);
			if (found)
				ret.emplace_back(curr_list);
		}
	}

	return ret;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline std::unique_ptr<SlideElement> FuncGraph<NodeId, NodeInfo, EdgeInfo>::clone() const {
	return std::make_unique<FuncGraph<NodeId, NodeInfo, EdgeInfo>>(*this);
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline DotCode FuncGraph<NodeId, NodeInfo, EdgeInfo>::draw_as_dot() const {
	std::stringstream ss;

	// configuration
	ss << "digraph {\n";
	ss << " ratio=\"fill\";\n";
	ss << " margin=\"0\";\n";
	ss << " outputorder=\"edgesfirst\";\n";
	ss << " overlap=false;\n";
	ss << " splines = true;\n";
	ss << " sep=\"+15,15\"\n";
	ss << " size=\"8,4.8\";\n";
	ss << " graph [fontname = \"Monospace\"];\n";
	ss << " node [fontname = \"Monospace\", shape=plain, fontsize=11];\n";
	ss << " edge [fontname = \"Monospace\", tailclip=false];\n";

	if (view_ == FuncGraphView::list) {
		// ranks
		ss << " rankdir = \"BT\";\n";
		ss << " { rank = same;";
		std::set<std::pair<const Node*, const Node*>> endpoints;
		for (const auto& nodes : find_all_cycles()) {
			endpoints.emplace(nodes[0], nodes.back());
			for (const auto& node : nodes)
				ss << node->id_ << ';';
		}
		ss << " }\n";
		// edges
		for (const auto& [id, edge] : edges_) {
			auto from = &nodes_.find(edge.from_)->second;
			auto to = &nodes_.find(edge.to_)->second;
			if (endpoints.find({from, to}) != endpoints.end())
				ss << ' ' << edge.to_dot(nodes_, 'n', 'n', {"constraint=false"}) << '\n';
			else
				ss << ' ' << edge.to_dot(nodes_) << '\n';
		}
		cerr << endl;
	}
	else {
		// edges
		for (const auto& [id, edge] : edges_)
			ss << ' ' << edge.to_dot(nodes_) << '\n';
	}

	// nodes
	for (auto& [id, node] : nodes_)
		ss << ' ' << node.to_dot() << '\n';

	ss << "}\n";

	return ss.str();
}

} // namespace valgo
