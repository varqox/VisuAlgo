#pragma once

#include "undirected_graph.h"

#include <queue>

namespace valgo {

template<class NodeId, class NodeInfo, class EdgeInfo>
class RootedGraph : public UndirectedGraph<NodeId, NodeInfo, EdgeInfo> {
protected:
	virtual std::string tool_name() const override;

	std::vector<NodeId> roots_;

	using UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::edges_;
	using UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::nodes_;
	using typename UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::Node;
	using typename UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::Edge;

	using typename UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::NodesIterator;
	using typename UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::NodesConstIterator;
	using typename UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::EdgesIterator;
	using typename UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::EdgesConstIterator;

	using UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::find_edge;

	// Returns pointres to all visited nodes reachable from st in bfs order.
	std::vector<const Node*> bfs(const Node* st, std::set<const Node*>& vis) const;

	// Returns pointers to nodes in bfs order.
	std::vector<const Node*> bfs_order() const;

public:
	RootedGraph() = default;
	RootedGraph(NodeId root);
	RootedGraph(std::vector<NodeId> roots);

	RootedGraph& set_root(NodeId root);
	RootedGraph& set_roots(std::vector<NodeId> roots);
	RootedGraph& unset_root();

	virtual std::unique_ptr<SlideElement> clone() const override;

	virtual DotCode draw_as_dot() const override;

	// fixing chaining
	virtual RootedGraph& add_node(const NodeId& node, std::optional<NodeInfo> node_info = std::nullopt) override {
		return UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::add_node(node, node_info), *this;
	}
	virtual RootedGraph& add_edge(const NodeId& from, const NodeId& to, std::optional<EdgeInfo> edge_info = std::nullopt) override {
		return UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::add_edge(from, to, edge_info), *this;
	}
	virtual RootedGraph& set_node_info(const NodeId& node, std::optional<NodeInfo> node_info) override {
		return UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::set_node_info(node, node_info), *this;
	}
	virtual RootedGraph& set_edge_info(const NodeId& from, const NodeId& to, std::optional<EdgeInfo> edge_info) override {
		return UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::set_edge_info(from, to, edge_info), *this;
	}
	virtual RootedGraph& set_node_color(const NodeId& node, std::optional<Color> color) override {
		return UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::set_node_color(node, color), *this;
	}
	virtual RootedGraph& set_every_node_color(const std::optional<Color>& color) override {
		return UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::set_every_node_color(color), *this;
	}
	virtual RootedGraph& set_edge_color(const NodeId& from, const NodeId& to, std::optional<Color> color) override {
		return UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::set_edge_color(from, to, color), *this;
	}
	virtual RootedGraph& set_every_edge_color(const std::optional<Color>& color) override {
		return UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::set_every_edge_color(color), *this;
	}
	virtual RootedGraph& hide_node(const NodeId& node) override {
		return UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::hide_node(node), *this;
	}
	virtual RootedGraph& hide_edge(const NodeId& from, const NodeId& to) override {
		return UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::hide_edge(from, to), *this;
	}
	virtual RootedGraph& unhide_node(const NodeId& node) override {
		return UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::unhide_node(node), *this;
	}
	virtual RootedGraph& unhide_edge(const NodeId& from, const NodeId& to) override {
		return UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::unhide_edge(from, to), *this;
	}
	virtual RootedGraph& remove_node(const NodeId& node) override {
		return UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::remove_node(node), *this;
	}
	virtual RootedGraph& remove_all_nodes() override {
		return UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::remove_all_nodes(), *this;
	}
	virtual RootedGraph& remove_edge(const NodeId& from, const NodeId& to) override {
		return UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::remove_edge(from, to), *this;
	}
	virtual RootedGraph& remove_all_edges() override {
		return UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::remove_all_edges(), *this;
	}
};

/****************** Implementation ******************/

template<class NodeId, class NodeInfo, class EdgeInfo>
inline std::string RootedGraph<NodeId, NodeInfo, EdgeInfo>::tool_name() const {
	return "dot";
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline std::vector<const typename RootedGraph<NodeId, NodeInfo, EdgeInfo>::Node*>
RootedGraph<NodeId, NodeInfo, EdgeInfo>::bfs(const Node* st, std::set<const Node*>& vis) const {
	std::queue<const Node*> q;
	std::vector<const Node*> ret;
	q.emplace(st);
	vis.emplace(st);
	ret.emplace_back(st);
	while (!q.empty()) {
		const Node* cur = q.front();
		q.pop();
		for (auto& nei_id : cur->nei_) {
			auto nei_ptr = &nodes_.find(nei_id)->second;
			if (vis.find(nei_ptr) == vis.end()) {
				q.emplace(nei_ptr);
				vis.emplace(nei_ptr);
				ret.emplace_back(nei_ptr);
			}
		}
	}
	return ret;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline std::vector<const typename RootedGraph<NodeId, NodeInfo, EdgeInfo>::Node*>
RootedGraph<NodeId, NodeInfo, EdgeInfo>::bfs_order() const {
	std::set<const Node*> vis;
	std::vector<const Node*> ret;

	// Start bfs from roots.
	for (auto& id : roots_) {
		auto it = nodes_.find(id);
		if (it != nodes_.end() && vis.find(&it->second) == vis.end()) {
			auto tmp = bfs(&it->second, vis);
			ret.insert(ret.end(), tmp.begin(), tmp.end());
		}
	}

	// Start bfs from other nodes.
	for (auto& [id, node] : nodes_) {
		if (vis.find(&node) == vis.end()) {
			auto tmp = bfs(&node, vis);
			ret.insert(ret.end(), tmp.begin(), tmp.end());
		}
	}

	return ret;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline RootedGraph<NodeId, NodeInfo, EdgeInfo>&
RootedGraph<NodeId, NodeInfo, EdgeInfo>::set_root(NodeId root) {
	roots_ = {std::move(root)};
	return *this;
}
template<class NodeId, class NodeInfo, class EdgeInfo>
inline RootedGraph<NodeId, NodeInfo, EdgeInfo>&
RootedGraph<NodeId, NodeInfo, EdgeInfo>::set_roots(std::vector<NodeId> roots) {
	roots_ = std::move(roots);
	return *this;
}
template<class NodeId, class NodeInfo, class EdgeInfo>
inline RootedGraph<NodeId, NodeInfo, EdgeInfo>&
RootedGraph<NodeId, NodeInfo, EdgeInfo>::unset_root() {
	roots_.clear();
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline std::unique_ptr<SlideElement> RootedGraph<NodeId, NodeInfo, EdgeInfo>::clone() const {
	return std::make_unique<RootedGraph<NodeId, NodeInfo, EdgeInfo>>(*this);
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline DotCode RootedGraph<NodeId, NodeInfo, EdgeInfo>::draw_as_dot() const {
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
	ss << " edge [fontname = \"Monospace\", arrowhead=none, headclip=false, tailclip=false];\n";

	// edges
	std::set<NodeId> drawn;
	for (auto* node : bfs_order()) {
		auto& id = node->id_;
		for (auto& nei_id : node->nei_) {
			auto* edge = &find_edge(id, nei_id)->second;
			// not yet drawn
			if (drawn.find(edge->from_) == drawn.end() && drawn.find(edge->to_) == drawn.end())
				ss << " " << edge->to_dot(nodes_, edge->to_ == id) << '\n';
		}
		drawn.emplace(id);
	}

	// nodes
	for (auto& [id, node] : nodes_)
		ss << " " << node.to_dot() << '\n';

	ss << "}\n";

	return ss.str();
}

} // namespace valgo
