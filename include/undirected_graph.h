#pragma once

#include "color.h"
#include "graph.h"

#include <map>
#include <optional>
#include <set>
#include <sstream>
#include <vector>

namespace valgo {

template<class NodeId, class NodeInfo, class EdgeInfo>
class UndirectedGraph : public Graph<NodeId, NodeInfo, EdgeInfo> {
protected:
	virtual std::string tool_name() const override;

	struct Node {
		NodeId id_;
		std::optional<NodeInfo> info_;
		std::optional<Color> color_;
		bool hidden_ = false;
		std::set<NodeId> nei_;

		Node(NodeId id, std::optional<NodeInfo> info = std::nullopt);

		DotCode to_dot() const;
	};

	struct Edge {
		NodeId from_;
		NodeId to_;
		std::optional<EdgeInfo> info_;
		std::optional<Color> color_;
		bool hidden_ = false;

		Edge(NodeId from, NodeId to, std::optional<EdgeInfo> info = std::nullopt);

		DotCode to_dot(const std::map<NodeId, Node>& nodes, bool reversed = false) const;
	};

	std::map<NodeId, Node> nodes_;
	std::map<std::pair<NodeId, NodeId>, Edge> edges_;

	using NodesIterator = typename std::map<NodeId, Node>::iterator;
	using NodesConstIterator = typename std::map<NodeId, Node>::const_iterator;

	using EdgesIterator = typename std::map<std::pair<NodeId, NodeId>, Edge>::iterator;
	using EdgesConstIterator = typename std::map<std::pair<NodeId, NodeId>, Edge>::const_iterator;

	std::vector<EdgesIterator> get_nei_edges(NodesIterator node);
	std::vector<EdgesConstIterator> get_nei_edges(NodesConstIterator node) const;

	EdgesIterator find_edge(const NodeId& a, const NodeId& b);
	EdgesConstIterator find_edge(const NodeId& a, const NodeId& b) const;

	void remove_edge(EdgesIterator edge);

	void remove_node(NodesIterator node);

	// Returns iterator to node with id @p node. If it does not exists it is created.
	NodesIterator find_or_add(const NodeId& node);

public:
	UndirectedGraph() = default;

	virtual UndirectedGraph& add_node(const NodeId& node, std::optional<NodeInfo> node_info = std::nullopt) override;

	virtual UndirectedGraph& add_edge(const NodeId& from, const NodeId& to,
	                                  std::optional<EdgeInfo> edge_info = std::nullopt) override;

	virtual UndirectedGraph& set_node_info(const NodeId& node, std::optional<NodeInfo> node_info) override;
	virtual UndirectedGraph& set_edge_info(const NodeId& from, const NodeId& to,
	                                       std::optional<EdgeInfo> edge_info) override;

	virtual UndirectedGraph& set_node_color(const NodeId& node, std::optional<Color> color) override;
	virtual UndirectedGraph& set_every_node_color(const std::optional<Color>& color) override;

	virtual UndirectedGraph& set_edge_color(const NodeId& from, const NodeId& to, std::optional<Color> color) override;
	virtual UndirectedGraph& set_every_edge_color(const std::optional<Color>& color) override;

	virtual UndirectedGraph& hide_node(const NodeId& node) override;
	virtual UndirectedGraph& hide_edge(const NodeId& from, const NodeId& to) override;

	virtual UndirectedGraph& unhide_node(const NodeId& node) override;
	virtual UndirectedGraph& unhide_edge(const NodeId& from, const NodeId& to) override;

	virtual UndirectedGraph& remove_node(const NodeId& node) override;
	virtual UndirectedGraph& remove_all_nodes() override;

	virtual UndirectedGraph& remove_edge(const NodeId& from, const NodeId& to) override;
	virtual UndirectedGraph& remove_all_edges() override;

	virtual std::unique_ptr<SlideElement> clone() const override;

	virtual DotCode draw_as_dot() const override;
	virtual LatexCode draw_as_latex() const override;
	virtual HTMLCode draw_as_html() const override;
};

/****************** Implementation ******************/

template<class NodeId, class NodeInfo, class EdgeInfo>
inline std::string UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::tool_name() const {
	return "neato";
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::Node::Node(NodeId id, std::optional<NodeInfo> info)
	: id_(std::move(id)), info_(std::move(info)) {}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline DotCode UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::Node::to_dot() const {
	std::stringstream ss;
	ss << id_ << " [";

	ss << "label=<<table width=\"50\" style=\"rounded\" border=\"1\" cellborder=\"0\" cellspacing=\"4\"";
	if (color_.has_value())
		ss << " bgcolor=\"#" << color_.value().to_hex() << "\"";
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
inline UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::Edge::Edge(NodeId from, NodeId to,
                                                               std::optional<EdgeInfo> info)
    : from_(std::move(from)), to_(std::move(to)), info_(std::move(info)) {}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline DotCode UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::Edge::to_dot(const std::map<NodeId, Node>& nodes,
                                                                         bool reversed) const {
	std::stringstream ss;
	std::string side = to_ == from_ ? ":n" : "";
	if (reversed)
		ss << to_ << side << " -> " << from_ << side;
	else
		ss << from_ << side << " -> " << to_ << side;
	ss << " [";

	auto is_hidden = [&](const NodeId &id) {
		const auto& it = nodes.find(id);
		return it->second.hidden_;
	};

	bool fst = true;
	if (info_.has_value()) {
		fst = false;
		ss << "label=\"" << info_.value() << "\"";
	}
	if (color_.has_value()) {
		if (!fst)
			ss << ", ";
		fst = false;
		ss << "color=\"#" << color_.value().to_hex() << "\"";
	}
	if (hidden_ || is_hidden(from_) || is_hidden(to_)) {
		if (!fst)
			ss << ", ";
		fst = false;
		ss << "style=invis";
	}

	ss << "];";

	return ss.str();
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline std::vector<typename UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::EdgesIterator>
UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::get_nei_edges(NodesIterator node) {
	std::vector<EdgesIterator> ret;
	for (auto& nei_id : node->second.nei_)
		ret.emplace_back(find_edge(node->second.id_, nei_id));
	return ret;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline std::vector<typename UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::EdgesConstIterator>
UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::get_nei_edges(NodesConstIterator node) const {
	std::vector<EdgesConstIterator> ret;
	for (auto& nei_id : node->second.nei_)
		ret.emplace_back(find_edge(node->second.id_, nei_id));
	return ret;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline typename UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::EdgesIterator
UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::find_edge(const NodeId& a, const NodeId& b) {
	auto it = edges_.find({a, b});
	if (it != edges_.end())
		return it;
	return edges_.find({b, a});
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline typename UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::EdgesConstIterator
UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::find_edge(const NodeId& a, const NodeId& b) const {
	auto it = edges_.find({a, b});
	if (it != edges_.end())
		return it;
	return edges_.find({b, a});
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline void UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::remove_edge(EdgesIterator edge) {
	auto it_from = nodes_.find(edge->second.from_);
	auto it_to = nodes_.find(edge->second.to_);
	it_from->second.nei_.erase(edge->second.to_);
	it_to->second.nei_.erase(edge->second.from_);
	edges_.erase(edge);
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline void UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::remove_node(NodesIterator node) {
	NodeId id = node->second.id_;
	for (NodeId nei_id : node->second.nei_) {
		auto nei_it = nodes_.find(nei_id);
		nei_it->second.nei_.erase(id);
		edges_.erase(find_edge(id, nei_id));
	}
	nodes_.erase(node);
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline typename UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::NodesIterator
UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::find_or_add(const NodeId& node) {
	auto it = nodes_.find(node);
	if (it == nodes_.end())
		it = nodes_.emplace(node, Node(node)).first;
	return it;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline UndirectedGraph<NodeId, NodeInfo, EdgeInfo>&
UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::add_node(const NodeId& node, std::optional<NodeInfo> node_info) {
	auto it = nodes_.find(node);
	if (it != nodes_.end())
		remove_node(it);
	nodes_.emplace(node, Node(node, std::move(node_info)));
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline UndirectedGraph<NodeId, NodeInfo, EdgeInfo>&
UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::add_edge(const NodeId& from, const NodeId& to,
                                                      std::optional<EdgeInfo> edge_info) {
	edges_.emplace(std::pair{from, to}, Edge(from, to, std::move(edge_info)));
	Node& it_from = find_or_add(from)->second;
	it_from.nei_.emplace(to);
	Node& it_to = find_or_add(to)->second;
	it_to.nei_.emplace(from);
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline UndirectedGraph<NodeId, NodeInfo, EdgeInfo>&
UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::set_node_info(const NodeId& node,
                                                           std::optional<NodeInfo> node_info) {
	auto it = nodes_.find(node);
	if (it != nodes_.end())
		it->second.info_ = std::move(node_info);
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline UndirectedGraph<NodeId, NodeInfo, EdgeInfo>&
UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::set_edge_info(const NodeId& from, const NodeId& to,
                                                           std::optional<EdgeInfo> edge_info) {
	auto it = find_edge(from, to);
	if (it != edges_.end())
		it->second.info_ = std::move(edge_info);
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline UndirectedGraph<NodeId, NodeInfo, EdgeInfo>&
UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::set_node_color(const NodeId& node, std::optional<Color> color) {
	auto it = nodes_.find(node);
	if (it != nodes_.end())
		it->second.color_ = std::move(color);
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline UndirectedGraph<NodeId, NodeInfo, EdgeInfo>&
UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::set_every_node_color(const std::optional<Color>& color) {
	for (auto& [id, node] : nodes_)
		node.color_ = color;
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline UndirectedGraph<NodeId, NodeInfo, EdgeInfo>&
UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::set_edge_color(const NodeId& from, const NodeId& to,
                                                            std::optional<Color> color) {
	auto it = find_edge(from, to);
	if (it != edges_.end())
		it->second.color_ = std::move(color);
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline UndirectedGraph<NodeId, NodeInfo, EdgeInfo>&
UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::set_every_edge_color(const std::optional<Color>& color) {
	for (auto& [id, edge] : edges_)
		edge.color_ = color;
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline UndirectedGraph<NodeId, NodeInfo, EdgeInfo>&
UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::hide_node(const NodeId& node) {
	auto it = nodes_.find(node);
	if (it != nodes_.end())
		it->second.hidden_ = true;
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline UndirectedGraph<NodeId, NodeInfo, EdgeInfo>&
UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::hide_edge(const NodeId& from, const NodeId& to) {
	auto it = find_edge(from, to);
	if (it != edges_.end())
		it->second.hidden_ = true;
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline UndirectedGraph<NodeId, NodeInfo, EdgeInfo>&
UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::unhide_node(const NodeId& node) {
	auto it = nodes_.find(node);
	if (it != nodes_.end())
		it->second.hidden_ = false;
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline UndirectedGraph<NodeId, NodeInfo, EdgeInfo>&
UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::unhide_edge(const NodeId& from, const NodeId& to) {
	auto it = find_edge(from, to);
	if (it != edges_.end())
		it->second.hidden_ = false;
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline UndirectedGraph<NodeId, NodeInfo, EdgeInfo>&
UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::remove_node(const NodeId& node) {
	auto it = nodes_.find(node);
	if (it != nodes_.end())
		remove_node(it);
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline UndirectedGraph<NodeId, NodeInfo, EdgeInfo>&
UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::remove_all_nodes() {
	nodes_.clear();
	edges_.clear();
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline UndirectedGraph<NodeId, NodeInfo, EdgeInfo>&
UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::remove_edge(const NodeId& from, const NodeId& to) {
	auto it = find_edge(from, to);
	if (it != edges_.end())
		remove_edge(it);
	return *this;
}

template <class NodeId, class NodeInfo, class EdgeInfo>
inline UndirectedGraph<NodeId, NodeInfo, EdgeInfo>&
UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::remove_all_edges() {
	for (auto& node : nodes_)
		node.second.nei_.clear();
	edges_.clear();
	return *this;
}

template<class NodeId, class NodeInfo, class EdgeInfo>
inline std::unique_ptr<SlideElement> UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::clone() const {
	return std::make_unique<UndirectedGraph<NodeId, NodeInfo, EdgeInfo>>(*this);
}

template<class NodeId, class NodeInfo, class EdgeInfo>
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

template<class NodeId, class NodeInfo, class EdgeInfo>
inline LatexCode UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::draw_as_latex() const {
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
inline HTMLCode UndirectedGraph<NodeId, NodeInfo, EdgeInfo>::draw_as_html() const {
	throw NotImplemented();
}

} // namespace valgo
