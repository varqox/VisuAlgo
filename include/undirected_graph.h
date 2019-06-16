#pragma once

#include "graph.h"

namespace valgo {

template <class NodeId, class NodeInfo, class EdgeInfo>
class UndirectedGraph : public Graph<NodeId, NodeInfo, EdgeInfo> {
protected:
	using Graph<NodeId, NodeInfo, EdgeInfo>::edges_;
	using Graph<NodeId, NodeInfo, EdgeInfo>::nodes_;
	using typename Graph<NodeId, NodeInfo, EdgeInfo>::Node;
	using typename Graph<NodeId, NodeInfo, EdgeInfo>::Edge;

	using NodesIterator = typename std::map<NodeId, Node>::iterator;
	using NodesConstIterator = typename std::map<NodeId, Node>::const_iterator;

	using EdgesIterator = typename std::map<std::pair<NodeId, NodeId>, Edge>::iterator;
	using EdgesConstIterator = typename std::map<std::pair<NodeId, NodeId>, Edge>::const_iterator;

	virtual EdgesIterator find_edge(const NodeId& a, const NodeId& b) override;
	virtual EdgesConstIterator find_edge(const NodeId& a, const NodeId& b) const override;

	virtual void remove_edge(EdgesIterator edge) override;
	virtual void remove_node(NodesIterator node) override;

	using Graph<NodeId, NodeInfo, EdgeInfo>::find_or_add;

public:
	UndirectedGraph() = default;

	virtual DotCode draw_as_dot() const override;

	virtual std::unique_ptr<SlideElement> clone() const override;

	virtual UndirectedGraph& add_edge(const NodeId& from, const NodeId& to,
	                                  std::optional<EdgeInfo> edge_info = std::nullopt) override;

	// fixing chaining
	virtual UndirectedGraph& add_node(const NodeId& node, std::optional<NodeInfo> node_info = std::nullopt) override {
		return Graph<NodeId, NodeInfo, EdgeInfo>::add_node(node, node_info), *this;
	}
	virtual UndirectedGraph& set_node_info(const NodeId& node, std::optional<NodeInfo> node_info) override {
		return Graph<NodeId, NodeInfo, EdgeInfo>::set_node_info(node, node_info), *this;
	}
	virtual UndirectedGraph& set_edge_info(const NodeId& from, const NodeId& to,
	                                       std::optional<EdgeInfo> edge_info) override {
		return Graph<NodeId, NodeInfo, EdgeInfo>::set_edge_info(from, to, edge_info), *this;
	}
	virtual UndirectedGraph& set_node_color(const NodeId& node, std::optional<Color> color) override {
		return Graph<NodeId, NodeInfo, EdgeInfo>::set_node_color(node, color), *this;
	}
	virtual UndirectedGraph& set_every_node_color(const std::optional<Color>& color) override {
		return Graph<NodeId, NodeInfo, EdgeInfo>::set_every_node_color(color), *this;
	}
	virtual UndirectedGraph& set_edge_color(const NodeId& from, const NodeId& to,
	                                        std::optional<Color> color) override {
		return Graph<NodeId, NodeInfo, EdgeInfo>::set_edge_color(from, to, color), *this;
	}
	virtual UndirectedGraph& set_every_edge_color(const std::optional<Color>& color) override {
		return Graph<NodeId, NodeInfo, EdgeInfo>::set_every_edge_color(color), *this;
	}
	virtual UndirectedGraph& hide_node(const NodeId& node) override {
		return Graph<NodeId, NodeInfo, EdgeInfo>::hide_node(node), *this;
	}
	virtual UndirectedGraph& hide_edge(const NodeId& from, const NodeId& to) override {
		return Graph<NodeId, NodeInfo, EdgeInfo>::hide_edge(from, to), *this;
	}
	virtual UndirectedGraph& unhide_node(const NodeId& node) override {
		return Graph<NodeId, NodeInfo, EdgeInfo>::unhide_node(node), *this;
	}
	virtual UndirectedGraph& unhide_edge(const NodeId& from, const NodeId& to) override {
		return Graph<NodeId, NodeInfo, EdgeInfo>::unhide_edge(from, to), *this;
	}
	virtual UndirectedGraph& remove_node(const NodeId& node) override {
		return Graph<NodeId, NodeInfo, EdgeInfo>::remove_node(node), *this;
	}
	virtual UndirectedGraph& remove_all_nodes() override {
		return Graph<NodeId, NodeInfo, EdgeInfo>::remove_all_nodes(), *this;
	}
	virtual UndirectedGraph& remove_edge(const NodeId& from, const NodeId& to) override {
		return Graph<NodeId, NodeInfo, EdgeInfo>::remove_edge(from, to), *this;
	}
	virtual UndirectedGraph& remove_all_edges() override {
		return Graph<NodeId, NodeInfo, EdgeInfo>::remove_all_edges(), *this;
	}
};

/****************** Implementation ******************/

template <class NodeId, class NodeInfo, class EdgeInfo>
inline typename UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::EdgesIterator
UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::find_edge(const NodeId& a, const NodeId& b) {
	auto it = edges_.find({a, b});
	if (it != edges_.end())
		return it;
	return edges_.find({b, a});
}

template <class NodeId, class NodeInfo, class EdgeInfo>
inline typename UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::EdgesConstIterator
UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::find_edge(const NodeId& a, const NodeId& b) const {
	auto it = edges_.find({a, b});
	if (it != edges_.end())
		return it;
	return edges_.find({b, a});
}

template <class NodeId, class NodeInfo, class EdgeInfo>
inline void UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::remove_edge(EdgesIterator edge) {
	auto it_from = nodes_.find(edge->second.from_);
	auto it_to = nodes_.find(edge->second.to_);
	it_from->second.nei_.erase(edge->second.to_);
	it_to->second.nei_.erase(edge->second.from_);
	edges_.erase(edge);
}

template <class NodeId, class NodeInfo, class EdgeInfo>
inline void UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::remove_node(NodesIterator node) {
	NodeId id = node->second.id_;
	for (NodeId nei_id : node->second.nei_) {
		auto nei_it = nodes_.find(nei_id);
		nei_it->second.nei_.erase(id);
		edges_.erase(find_edge(id, nei_id));
	}
	nodes_.erase(node);
}

template <class NodeId, class NodeInfo, class EdgeInfo>
inline UndirectedGraph<NodeId, NodeInfo, EdgeInfo>&
UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::add_edge(const NodeId& from, const NodeId& to,
                                                      std::optional<EdgeInfo> edge_info) {
	auto it = find_edge(from, to);
	if (it == edges_.end()) {
		edges_.emplace(std::pair{from, to}, Edge(from, to, std::move(edge_info)));
		Node& it_from = find_or_add(from)->second;
		it_from.nei_.emplace(to);
		Node& it_to = find_or_add(to)->second;
		it_to.nei_.emplace(from);
	} else
		it->second.info_ = edge_info;

	return *this;
}

template <class NodeId, class NodeInfo, class EdgeInfo>
inline DotCode UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::draw_as_dot() const {
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
	for (const auto& [id, edge] : edges_)
		ss << " " << edge.to_dot(nodes_) << '\n';

	// nodes
	for (const auto& [id, node] : nodes_)
		ss << " " << node.to_dot() << '\n';

	ss << "}\n";

	return ss.str();
}

template <class NodeId, class NodeInfo, class EdgeInfo>
inline std::unique_ptr<SlideElement> UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::clone() const {
	return std::make_unique<UndirectedGraph<NodeId, NodeInfo, EdgeInfo>>(*this);
}

} // namespace valgo
