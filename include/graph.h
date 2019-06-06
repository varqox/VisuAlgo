#pragma once

#include "color.h"
#include "slide_element.h"

#include <map>
#include <optional>
#include <set>
#include <sstream>
#include <vector>

namespace valgo {

using DotCode = std::string;

template<class NodeId, class NodeInfo, class EdgeInfo>
class Graph : public SlideElement {
protected:
	// Tool to draw graph, default neato
	virtual std::string tool_name() const;

	struct Node {
		NodeId id_;
		std::optional<NodeInfo> info_;
		std::optional<Color> color_;
		bool hidden_ = false;
		std::set<NodeId> nei_;

		Node(NodeId id, std::optional<NodeInfo> info = std::nullopt);

		virtual DotCode to_dot() const;
	};

	struct Edge {
		NodeId from_;
		NodeId to_;
		std::optional<EdgeInfo> info_;
		std::optional<Color> color_;
		bool hidden_ = false;

		Edge(NodeId from, NodeId to, std::optional<EdgeInfo> info = std::nullopt);

		virtual DotCode to_dot(const std::map<NodeId, Node>& nodes, bool reversed = false) const;
		virtual DotCode to_dot(const std::map<NodeId, Node>& nodes, std::optional<char> side_from,
			std::optional<char> side_to, const std::vector<std::string>& opts = {}, bool reversed = false) const;
	};

	std::map<NodeId, Node> nodes_;
	std::map<std::pair<NodeId, NodeId>, Edge> edges_;

	using NodesIterator = typename std::map<NodeId, Node>::iterator;
	using NodesConstIterator = typename std::map<NodeId, Node>::const_iterator;

	using EdgesIterator = typename std::map<std::pair<NodeId, NodeId>, Edge>::iterator;
	using EdgesConstIterator = typename std::map<std::pair<NodeId, NodeId>, Edge>::const_iterator;

	virtual std::vector<EdgesIterator> get_nei_edges(NodesIterator node);
	virtual std::vector<EdgesConstIterator> get_nei_edges(NodesConstIterator node) const;

	// Returns iterator to edge from a to b in edges_
	virtual EdgesIterator find_edge(const NodeId& a, const NodeId& b) = 0;
	virtual EdgesConstIterator find_edge(const NodeId& a, const NodeId& b) const = 0;

	virtual void remove_edge(EdgesIterator edge) = 0;
	// Removes node and all adjacent edges
	virtual void remove_node(NodesIterator node) = 0;

	// Returns iterator to node with id @p node. If it does not exists it is created.
	virtual NodesIterator find_or_add(const NodeId& node);
public:
	Graph() = default;

	// If @p node exists it is replaced by a new node.
	virtual Graph& add_node(const NodeId& node, std::optional<NodeInfo> node_info = std::nullopt);

	// If @p edge exists it is replaced by a new edge.
	// @p from and @p to are created if they don't exist.
	virtual Graph& add_edge(const NodeId& from, const NodeId& to, std::optional<EdgeInfo> edge_info = std::nullopt) = 0;

	virtual Graph& set_node_info(const NodeId& node, std::optional<NodeInfo> node_info);
	virtual Graph& set_edge_info(const NodeId& from, const NodeId& to, std::optional<EdgeInfo> edge_info);

	virtual Graph& set_node_color(const NodeId& node, std::optional<Color> color);
	virtual Graph& set_every_node_color(const std::optional<Color>& color);

	virtual Graph& set_edge_color(const NodeId& from, const NodeId& to, std::optional<Color> color);
	virtual Graph& set_every_edge_color(const std::optional<Color>& color);

	// Hiding does not affect nodes and edges positions
	virtual Graph& hide_node(const NodeId& node);
	// Hiding does not affect nodes and edges positions
	virtual Graph& hide_edge(const NodeId& from, const NodeId& to);

	virtual Graph& unhide_node(const NodeId& node);
	virtual Graph& unhide_edge(const NodeId& from, const NodeId& to);

	virtual Graph& remove_node(const NodeId& node);
	virtual Graph& remove_all_nodes();

	virtual Graph& remove_edge(const NodeId& from, const NodeId& to);
	virtual Graph& remove_all_edges();

	virtual DotCode draw_as_latex() const;
	virtual DotCode draw_as_html() const;

	virtual DotCode draw_as_dot() const = 0;
};

/****************** Implementation ******************/

template<class NodeId, class NodeInfo, class EdgeInfo>
inline std::string Graph<NodeId, NodeInfo, EdgeInfo>::tool_name() const {
	return "neato";
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline Graph<NodeId, NodeInfo, EdgeInfo>::Node::Node(NodeId id, std::optional<NodeInfo> info)
	: id_(std::move(id)), info_(std::move(info)) {}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline DotCode Graph<NodeId, NodeInfo, EdgeInfo>::Node::to_dot() const {
	std::stringstream ss;
	ss << '"' << id_ << "\" [";

	ss << "label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\"";
	if (color_.has_value())
		ss << " bgcolor=\"#" << color_.value().to_hex() << "\"";
	else
		ss << " bgcolor=\"white\"";
	ss << "><tr><td width=\"50\">" << id_ << "</td></tr>";
	if (info_.has_value())
		ss << "<hr/><tr><td width=\"50\">" << info_.value() << "</td></tr>"; // TODO: ogarnac string to html
	ss << "</table>>";
	if (hidden_)
		ss << ", style=invis";

	ss << "];";

	return ss.str();
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline Graph<NodeId, NodeInfo, EdgeInfo>::Edge::Edge(NodeId from, NodeId to, std::optional<EdgeInfo> info)
    : from_(std::move(from)), to_(std::move(to)), info_(std::move(info)) {}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline DotCode Graph<NodeId, NodeInfo, EdgeInfo>::Edge::to_dot(const std::map<NodeId, Node>& nodes,
		std::optional<char> side_from, std::optional<char> side_to, const std::vector<std::string>& opts,
		bool reversed) const {
	std::stringstream ss;

	auto print_node = [](const Node& node, std::optional<char> side) {
		std::stringstream sss;
		sss << '"' << node.id_ << '"';
		if (side.has_value())
			sss << ':' << side.value();
		return sss.str();
	};

	if (reversed)
		ss << print_node(to_, side_to) << " -> " << print_node(from_, side_from);
	else
		ss << print_node(from_, side_from) << " -> " << print_node(to_, side_to);
	ss << " [";

	auto is_hidden = [&](const NodeId &id) {
		const auto& it = nodes.find(id);
		return it->second.hidden_;
	};

	if (info_.has_value())
		ss << "label=\"" << info_.value() << "\",";
	if (color_.has_value())
		ss << "color=\"#" << color_.value().to_hex() << "\",";
	if (hidden_ || is_hidden(from_) || is_hidden(to_))
		ss << "style=invis,";
	for (const auto &i : opts)
		ss << i << ',';

	ss << "];";

	return ss.str();
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline DotCode Graph<NodeId, NodeInfo, EdgeInfo>::Edge::to_dot(const std::map<NodeId, Node>& nodes,
		bool reversed) const {
	return from_ == to_ ? to_dot(nodes, 'n', 'n', {}, reversed)
	                    : to_dot(nodes, std::nullopt, std::nullopt, {}, reversed);
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline std::vector<typename Graph<NodeId, NodeInfo, EdgeInfo>::EdgesIterator>
Graph<NodeId, NodeInfo, EdgeInfo>::get_nei_edges(NodesIterator node) {
	std::vector<EdgesIterator> ret;
	for (auto& nei_id : node->second.nei_)
		ret.emplace_back(find_edge(node->second.id_, nei_id));
	return ret;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline std::vector<typename Graph<NodeId, NodeInfo, EdgeInfo>::EdgesConstIterator>
Graph<NodeId, NodeInfo, EdgeInfo>::get_nei_edges(NodesConstIterator node) const {
	std::vector<EdgesConstIterator> ret;
	for (auto& nei_id : node->second.nei_)
		ret.emplace_back(find_edge(node->second.id_, nei_id));
	return ret;
}


template<class NodeId, class NodeInfo, class EdgeInfo>
inline typename Graph<NodeId, NodeInfo, EdgeInfo>::NodesIterator
Graph<NodeId, NodeInfo, EdgeInfo>::find_or_add(const NodeId& node) {
	auto it = nodes_.find(node);
	if (it == nodes_.end())
		it = nodes_.emplace(node, Node(node)).first;
	return it;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline Graph<NodeId, NodeInfo, EdgeInfo>&
Graph<NodeId, NodeInfo, EdgeInfo>::add_node(const NodeId& node, std::optional<NodeInfo> node_info) {
	auto it = nodes_.find(node);
	if (it != nodes_.end())
		remove_node(it);
	nodes_.emplace(node, Node(node, std::move(node_info)));
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline Graph<NodeId, NodeInfo, EdgeInfo>&
Graph<NodeId, NodeInfo, EdgeInfo>::set_node_info(const NodeId& node, std::optional<NodeInfo> node_info) {
	auto it = nodes_.find(node);
	if (it != nodes_.end())
		it->second.info_ = std::move(node_info);
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline Graph<NodeId, NodeInfo, EdgeInfo>&
Graph<NodeId, NodeInfo, EdgeInfo>::set_edge_info(const NodeId& from, const NodeId& to,
                                                         std::optional<EdgeInfo> edge_info) {
	auto it = find_edge(from, to);
	if (it != edges_.end())
		it->second.info_ = std::move(edge_info);
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline Graph<NodeId, NodeInfo, EdgeInfo>&
Graph<NodeId, NodeInfo, EdgeInfo>::set_node_color(const NodeId& node, std::optional<Color> color) {
	auto it = nodes_.find(node);
	if (it != nodes_.end())
		it->second.color_ = std::move(color);
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline Graph<NodeId, NodeInfo, EdgeInfo>&
Graph<NodeId, NodeInfo, EdgeInfo>::set_every_node_color(const std::optional<Color>& color) {
	for (auto& [id, node] : nodes_)
		node.color_ = color;
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline Graph<NodeId, NodeInfo, EdgeInfo>&
Graph<NodeId, NodeInfo, EdgeInfo>::set_edge_color(const NodeId& from, const NodeId& to,
                                                          std::optional<Color> color) {
	auto it = find_edge(from, to);
	if (it != edges_.end())
		it->second.color_ = std::move(color);
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline Graph<NodeId, NodeInfo, EdgeInfo>&
Graph<NodeId, NodeInfo, EdgeInfo>::set_every_edge_color(const std::optional<Color>& color) {
	for (auto& [id, edge] : edges_)
		edge.color_ = color;
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline Graph<NodeId, NodeInfo, EdgeInfo>&
Graph<NodeId, NodeInfo, EdgeInfo>::hide_node(const NodeId& node) {
	auto it = nodes_.find(node);
	if (it != nodes_.end())
		it->second.hidden_ = true;
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline Graph<NodeId, NodeInfo, EdgeInfo>&
Graph<NodeId, NodeInfo, EdgeInfo>::hide_edge(const NodeId& from, const NodeId& to) {
	auto it = find_edge(from, to);
	if (it != edges_.end())
		it->second.hidden_ = true;
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline Graph<NodeId, NodeInfo, EdgeInfo>&
Graph<NodeId, NodeInfo, EdgeInfo>::unhide_node(const NodeId& node) {
	auto it = nodes_.find(node);
	if (it != nodes_.end())
		it->second.hidden_ = false;
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline Graph<NodeId, NodeInfo, EdgeInfo>&
Graph<NodeId, NodeInfo, EdgeInfo>::unhide_edge(const NodeId& from, const NodeId& to) {
	auto it = find_edge(from, to);
	if (it != edges_.end())
		it->second.hidden_ = false;
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline Graph<NodeId, NodeInfo, EdgeInfo>&
Graph<NodeId, NodeInfo, EdgeInfo>::remove_node(const NodeId& node) {
	auto it = nodes_.find(node);
	if (it != nodes_.end())
		remove_node(it);
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline Graph<NodeId, NodeInfo, EdgeInfo>&
Graph<NodeId, NodeInfo, EdgeInfo>::remove_all_nodes() {
	nodes_.clear();
	edges_.clear();
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline Graph<NodeId, NodeInfo, EdgeInfo>&
Graph<NodeId, NodeInfo, EdgeInfo>::remove_edge(const NodeId& from, const NodeId& to) {
	auto it = find_edge(from, to);
	if (it != edges_.end())
		remove_edge(it);
	return *this;
}

template <class NodeId, class NodeInfo, class EdgeInfo>
inline Graph<NodeId, NodeInfo, EdgeInfo>&
Graph<NodeId, NodeInfo, EdgeInfo>::remove_all_edges() {
	for (auto& node : nodes_)
		node.second.nei_.clear();
	edges_.clear();
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline LatexCode Graph<NodeId, NodeInfo, EdgeInfo>::draw_as_latex() const {
	std::stringstream ss;

	ss << "\\begin{figure}\n";
	// name of a tool
	ss << "\\begin{graphviz}{" << tool_name() << "}\n";

	// graph
	ss << draw_as_dot();

	ss << "\\end{graphviz}\n";
	ss << "\\end{figure}";

	return ss.str();
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline HTMLCode Graph<NodeId, NodeInfo, EdgeInfo>::draw_as_html() const {
	throw NotImplemented();
}

} // namespace valgo
