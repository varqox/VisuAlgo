#pragma once

#include "color.h"
#include "slide_element.h"

#include <map>
#include <optional>
#include <vector>

namespace valgo {

using DOTCode = std::string;

template<class NodeId, class NodeInfo, class EdgeInfo>
class Graph : public SlideElement {
public:
	Graph() = default;

	// If @p node exists it is replaced by a new node.
	virtual Graph& add_node(const NodeId& node, std::optional<NodeInfo> node_info = std::nullopt) = 0;

	// If @p edge exists it is replaced by a new edge.
	// @p from and @p to are created if they don't exist.
	virtual Graph& add_edge(const NodeId& from, const NodeId& to, std::optional<EdgeInfo> edge_info = std::nullopt) = 0;

	virtual Graph& set_node_info(const NodeId& node, std::optional<NodeInfo> node_info) = 0;
	virtual Graph& set_edge_info(const NodeId& from, const NodeId& to, std::optional<EdgeInfo> edge_info) = 0;

	virtual Graph& set_node_color(const NodeId& node, std::optional<Color> color) = 0;
	virtual Graph& set_every_node_color(const std::optional<Color>& color) = 0;

	virtual Graph& set_edge_color(const NodeId& from, const NodeId& to, std::optional<Color> color) = 0;
	virtual Graph& set_every_edge_color(const std::optional<Color>& color) = 0;

	virtual Graph& hide_node(const NodeId& node) = 0;
	virtual Graph& hide_edge(const NodeId& from, const NodeId& to) = 0;

	virtual Graph& unhide_node(const NodeId& node) = 0;
	virtual Graph& unhide_edge(const NodeId& from, const NodeId& to) = 0;

	virtual Graph& remove_node(const NodeId& node) = 0;
	virtual Graph& remove_all_nodes() = 0;

	virtual Graph& remove_edge(const NodeId& from, const NodeId& to) = 0;
	virtual Graph& remove_all_edges() = 0;
};

} // namespace valgo
