#pragma once

#include "directed_graph.h"

#include <queue>

namespace valgo {

enum class AcyclicGraphView { SPARSE, LIST };

template <class NodeId, class NodeInfo, class EdgeInfo>
class AcyclicGraph : public DirectedGraph<NodeId, NodeInfo, EdgeInfo> {
protected:
	virtual std::string tool_name() const override;

	AcyclicGraphView view_;

	using DirectedGraph<NodeId, NodeInfo, EdgeInfo>::edges_;
	using DirectedGraph<NodeId, NodeInfo, EdgeInfo>::nodes_;

public:
	AcyclicGraph(AcyclicGraphView view = AcyclicGraphView::SPARSE) : view_(view) {}

	AcyclicGraph& set_view(AcyclicGraphView view) {
		view_ = view;
		return *this;
	}

	virtual std::unique_ptr<SlideElement> clone() const override;

	virtual DotCode draw_as_dot() const override;

	// fixing chaining
	virtual AcyclicGraph& add_node(const NodeId& node, std::optional<NodeInfo> node_info = std::nullopt) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::add_node(node, node_info), *this;
	}
	virtual AcyclicGraph& add_edge(const NodeId& from, const NodeId& to,
			std::optional<EdgeInfo> edge_info = std::nullopt) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::add_edge(from, to, edge_info), *this;
	}
	virtual AcyclicGraph& set_node_info(const NodeId& node, std::optional<NodeInfo> node_info) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::set_node_info(node, node_info), *this;
	}
	virtual AcyclicGraph& set_edge_info(const NodeId& from, const NodeId& to,
			std::optional<EdgeInfo> edge_info) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::set_edge_info(from, to, edge_info), *this;
	}
	virtual AcyclicGraph& set_node_color(const NodeId& node, std::optional<Color> color) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::set_node_color(node, color), *this;
	}
	virtual AcyclicGraph& set_every_node_color(const std::optional<Color>& color) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::set_every_node_color(color), *this;
	}
	virtual AcyclicGraph& set_edge_color(const NodeId& from, const NodeId& to, std::optional<Color> color) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::set_edge_color(from, to, color), *this;
	}
	virtual AcyclicGraph& set_every_edge_color(const std::optional<Color>& color) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::set_every_edge_color(color), *this;
	}
	virtual AcyclicGraph& hide_node(const NodeId& node) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::hide_node(node), *this;
	}
	virtual AcyclicGraph& hide_edge(const NodeId& from, const NodeId& to) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::hide_edge(from, to), *this;
	}
	virtual AcyclicGraph& unhide_node(const NodeId& node) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::unhide_node(node), *this;
	}
	virtual AcyclicGraph& unhide_edge(const NodeId& from, const NodeId& to) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::unhide_edge(from, to), *this;
	}
	virtual AcyclicGraph& remove_node(const NodeId& node) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::remove_node(node), *this;
	}
	virtual AcyclicGraph& remove_all_nodes() override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::remove_all_nodes(), *this;
	}
	virtual AcyclicGraph& remove_edge(const NodeId& from, const NodeId& to) override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::remove_edge(from, to), *this;
	}
	virtual AcyclicGraph& remove_all_edges() override {
		return DirectedGraph<NodeId, NodeInfo, EdgeInfo>::remove_all_edges(), *this;
	}
};

/****************** Implementation ******************/

template<class NodeId, class NodeInfo, class EdgeInfo>
inline std::string AcyclicGraph<NodeId, NodeInfo, EdgeInfo>::tool_name() const {
	return "dot";
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline std::unique_ptr<SlideElement> AcyclicGraph<NodeId, NodeInfo, EdgeInfo>::clone() const {
	return std::make_unique<AcyclicGraph<NodeId, NodeInfo, EdgeInfo>>(*this);
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline DotCode AcyclicGraph<NodeId, NodeInfo, EdgeInfo>::draw_as_dot() const {
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

	switch (view_) {
	case AcyclicGraphView::SPARSE:
		break;

	case AcyclicGraphView::LIST: {
		ss << " { rank = same;";
		for (const auto& [id, node] : nodes_)
			ss << id << ';';
		ss << " }\n";
		break;
	}
	}

	// edges
	for (const auto& [id, edge] : edges_)
		ss << " " << edge.to_dot(nodes_) << '\n';

	// nodes
	for (const auto& [id, node] : nodes_)
		ss << " " << node.to_dot() << '\n';

	ss << "}\n";

	return ss.str();
}

} // namespace valgo
